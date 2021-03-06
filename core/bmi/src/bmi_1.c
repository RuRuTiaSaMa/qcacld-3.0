/*
 * copyright (c) 2014-2015 The Linux Foundation. All rights reserved.
 *
 * Previously licensed under the ISC license by Qualcomm Atheros, Inc.
 *
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * This file was originally distributed by Qualcomm Atheros, Inc.
 * under proprietary terms before Copyright ownership was assigned
 * to the Linux Foundation.
 */

#include "i_bmi.h"

/* APIs visible to the driver */

CDF_STATUS
bmi_read_memory(uint32_t address,
		uint8_t *buffer, uint32_t length, struct ol_softc *scn)
{
	uint32_t cid;
	int status;
	uint32_t offset;
	uint32_t remaining, rxlen;
	uint8_t *bmi_cmd_buff = scn->bmi_cmd_buff;
	uint8_t *bmi_rsp_buff = scn->bmi_rsp_buff;
	uint32_t align;

	if (scn->bmi_done) {
		BMI_DBG("command disallowed");
		return CDF_STATUS_E_PERM;
	}

	if (!scn->bmi_cmd_buff || !scn->bmi_rsp_buff) {
		BMI_ERR("BMI Initialization hasn't done");
		return CDF_STATUS_NOT_INITIALIZED;
	}

	bmi_assert(BMI_COMMAND_FITS(BMI_DATASZ_MAX + sizeof(cid) +
			sizeof(address) + sizeof(length)));
	cdf_mem_set(bmi_cmd_buff, 0, BMI_DATASZ_MAX + sizeof(cid) +
			sizeof(address) + sizeof(length));
	cdf_mem_set(bmi_rsp_buff, 0, BMI_DATASZ_MAX + sizeof(cid) +
			sizeof(address) + sizeof(length));

	BMI_DBG("BMI Read: device: 0x%p, address: 0x%x, length: %d",
						scn, address, length);

	cid = BMI_READ_MEMORY;
	align = 0;
	remaining = length;

	while (remaining) {
		rxlen = (remaining < BMI_DATASZ_MAX) ?
				remaining : BMI_DATASZ_MAX;
		offset = 0;
		cdf_mem_copy(&(bmi_cmd_buff[offset]), &cid, sizeof(cid));
		offset += sizeof(cid);
		cdf_mem_copy(&(bmi_cmd_buff[offset]), &address,
						sizeof(address));
		offset += sizeof(address);
		cdf_mem_copy(&(bmi_cmd_buff[offset]), &rxlen, sizeof(rxlen));
		offset += sizeof(length);

		/* note we reuse the same buffer to receive on */
		status = hif_exchange_bmi_msg(scn, bmi_cmd_buff, offset,
				bmi_rsp_buff, &rxlen, BMI_EXCHANGE_TIMEOUT_MS);
		if (status) {
			BMI_ERR("Unable to read from the device");
			return CDF_STATUS_E_FAILURE;
		}
		if (remaining == rxlen) {
			cdf_mem_copy(&buffer[length - remaining + align],
					bmi_rsp_buff, rxlen - align);
			/* last align bytes are invalid */
		} else {
			cdf_mem_copy(&buffer[length - remaining + align],
				 bmi_rsp_buff, rxlen);
		}
		remaining -= rxlen;
		address += rxlen;
	}

	BMI_DBG("BMI Read Memory: Exit");
	return CDF_STATUS_SUCCESS;
}

CDF_STATUS
bmi_write_memory(uint32_t address,
		 uint8_t *buffer, uint32_t length, struct ol_softc *scn)
{
	uint32_t cid;
	int status;
	uint32_t offset;
	uint32_t remaining, txlen;
	const uint32_t header = sizeof(cid) + sizeof(address) + sizeof(length);
	uint8_t aligned_buffer[BMI_DATASZ_MAX];
	uint8_t *src;
	uint8_t *bmi_cmd_buff = scn->bmi_cmd_buff;

	if (scn->bmi_done) {
		BMI_ERR("Command disallowed");
		return CDF_STATUS_E_PERM;
	}

	if (!bmi_cmd_buff) {
		BMI_ERR("BMI initialization hasn't done");
		return CDF_STATUS_E_PERM;
	}

	bmi_assert(BMI_COMMAND_FITS(BMI_DATASZ_MAX + header));
	cdf_mem_set(bmi_cmd_buff, 0, BMI_DATASZ_MAX + header);

	BMI_DBG("BMI Write Memory:device: 0x%p, address: 0x%x, length: %d",
						scn, address, length);

	cid = BMI_WRITE_MEMORY;

	remaining = length;
	while (remaining) {
		src = &buffer[length - remaining];
		if (remaining < (BMI_DATASZ_MAX - header)) {
			if (remaining & 3) {
				/* align it with 4 bytes */
				remaining = remaining + (4 - (remaining & 3));
				memcpy(aligned_buffer, src, remaining);
				src = aligned_buffer;
			}
			txlen = remaining;
		} else {
			txlen = (BMI_DATASZ_MAX - header);
		}
		offset = 0;
		cdf_mem_copy(&(bmi_cmd_buff[offset]), &cid, sizeof(cid));
		offset += sizeof(cid);
		cdf_mem_copy(&(bmi_cmd_buff[offset]), &address,
						sizeof(address));
		offset += sizeof(address);
		cdf_mem_copy(&(bmi_cmd_buff[offset]), &txlen, sizeof(txlen));
		offset += sizeof(txlen);
		cdf_mem_copy(&(bmi_cmd_buff[offset]), src, txlen);
		offset += txlen;
		status = hif_exchange_bmi_msg(scn, bmi_cmd_buff, offset,
					NULL, NULL, BMI_EXCHANGE_TIMEOUT_MS);
		if (status) {
			BMI_ERR("Unable to write to the device; status:%d",
								status);
			return CDF_STATUS_E_FAILURE;
		}
		remaining -= txlen;
		address += txlen;
	}

	BMI_DBG("BMI Write Memory: Exit");

	return CDF_STATUS_SUCCESS;
}

CDF_STATUS
bmi_execute(uint32_t address, A_UINT32 *param, struct ol_softc *scn)
{
	uint32_t cid;
	int status;
	uint32_t offset;
	uint32_t param_len;
	uint8_t *bmi_cmd_buff = scn->bmi_cmd_buff;
	uint8_t *bmi_rsp_buff = scn->bmi_rsp_buff;
	uint32_t size = sizeof(cid) + sizeof(address) + sizeof(param);

	if (scn->bmi_done) {
		BMI_ERR("Command disallowed");
		return CDF_STATUS_E_PERM;
	}

	if (!bmi_cmd_buff || !bmi_rsp_buff) {
		BMI_ERR("%s:BMI CMD/RSP Buffer is NULL", __func__);
		return CDF_STATUS_NOT_INITIALIZED;
	}

	bmi_assert(BMI_COMMAND_FITS(size));
	cdf_mem_set(bmi_cmd_buff, 0, size);
	cdf_mem_set(bmi_rsp_buff, 0, size);


	BMI_DBG("BMI Execute: device: 0x%p, address: 0x%x, param: %d",
						scn, address, *param);

	cid = BMI_EXECUTE;

	offset = 0;
	cdf_mem_copy(&(bmi_cmd_buff[offset]), &cid, sizeof(cid));
	offset += sizeof(cid);
	cdf_mem_copy(&(bmi_cmd_buff[offset]), &address, sizeof(address));
	offset += sizeof(address);
	cdf_mem_copy(&(bmi_cmd_buff[offset]), param, sizeof(*param));
	offset += sizeof(*param);
	param_len = sizeof(*param);
	status = hif_exchange_bmi_msg(scn, bmi_cmd_buff, offset,
					bmi_rsp_buff, &param_len, 0);
	if (status) {
		BMI_ERR("Unable to read from the device status:%d", status);
		return CDF_STATUS_E_FAILURE;
	}

	cdf_mem_copy(param, bmi_rsp_buff, sizeof(*param));

	BMI_DBG("BMI Execute: Exit (param: %d)", *param);
	return CDF_STATUS_SUCCESS;
}

inline CDF_STATUS
bmi_no_command(struct ol_softc *scn)
{
	return CDF_STATUS_SUCCESS;
}

CDF_STATUS
bmi_firmware_download(struct ol_softc *scn)
{
	CDF_STATUS status;
	struct bmi_target_info targ_info;
	cdf_mem_zero(&targ_info, sizeof(targ_info));

	/* Initialize BMI */
	status = bmi_init(scn);
	if (status != CDF_STATUS_SUCCESS) {
		BMI_ERR("BMI Initialization Failed err:%d", status);
		return status;
	}

	/* Get target information */
	status = bmi_get_target_info(&targ_info, scn);
	if (status != CDF_STATUS_SUCCESS) {
		BMI_ERR("BMI Target Info get failed: status:%d", status);
		return status;
	}

	scn->target_type = targ_info.target_type;
	scn->target_version = targ_info.target_ver;

	/* Configure target */
	status = ol_configure_target(scn);
	if (status != CDF_STATUS_SUCCESS) {
		BMI_ERR("BMI Configure Target Failed status:%d", status);
		return status;
	}

	status = ol_download_firmware(scn);
	if (status != CDF_STATUS_SUCCESS)
		BMI_ERR("BMI Download Firmware Failed Status:%d", status);

	return status;
}

CDF_STATUS bmi_done_local(struct ol_softc *scn)
{
	int status;
	uint32_t cid;

	if (!scn) {
		BMI_ERR("Invalid scn context");
		bmi_assert(0);
		return CDF_STATUS_NOT_INITIALIZED;
	}

	if (scn->bmi_done) {
		BMI_DBG("bmi_done_local skipped");
		return CDF_STATUS_E_PERM;
	}

	BMI_DBG("BMI Done: Enter (device: 0x%p)", scn);

	scn->bmi_done = true;
	cid = BMI_DONE;

	if (!scn->bmi_cmd_buff) {
		BMI_ERR("Invalid scn BMICmdBuff");
		bmi_assert(0);
		return CDF_STATUS_NOT_INITIALIZED;
	}

	cdf_mem_copy(scn->bmi_cmd_buff, &cid, sizeof(cid));

	status = hif_exchange_bmi_msg(scn, scn->bmi_cmd_buff,
				sizeof(cid), NULL, NULL, 0);
	if (status) {
		BMI_ERR("Failed to write to the device; status:%d", status);
		return CDF_STATUS_E_FAILURE;
	}

	if (scn->bmi_cmd_buff) {
		cdf_os_mem_free_consistent(scn->cdf_dev, MAX_BMI_CMDBUF_SZ,
				    scn->bmi_cmd_buff, scn->bmi_cmd_da, 0);
		scn->bmi_cmd_buff = NULL;
		scn->bmi_cmd_da = 0;
	}

	if (scn->bmi_rsp_buff) {
		cdf_os_mem_free_consistent(scn->cdf_dev, MAX_BMI_CMDBUF_SZ,
				    scn->bmi_rsp_buff, scn->bmi_rsp_da, 0);
		scn->bmi_rsp_buff = NULL;
		scn->bmi_rsp_da = 0;
	}

	return CDF_STATUS_SUCCESS;
}
