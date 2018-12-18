/*
 * Copyright (c) 2018 The Linux Foundation. All rights reserved.
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

/**
 * DOC: contains NAN INI configurations
 */

#include "wlan_objmgr_psoc_obj.h"
#include "cfg_nan_api.h"
#include "../../core/src/nan_main_i.h"

static inline struct nan_psoc_priv_obj
		 *cfg_nan_get_priv_obj(struct wlan_objmgr_psoc *psoc)
{
	if (!psoc) {
		nan_err("PSOC obj null");
		return NULL;
	}
	return wlan_objmgr_psoc_get_comp_private_obj(psoc, WLAN_UMAC_COMP_NAN);
}

bool cfg_nan_get_enable(struct wlan_objmgr_psoc *psoc)
{
	struct nan_psoc_priv_obj *nan_obj = cfg_nan_get_priv_obj(psoc);

	if (!nan_obj) {
		nan_err("NAN obj null");
		return false;
	}
	return nan_obj->cfg_param.enable;
}

bool cfg_nan_get_datapath_enable(struct wlan_objmgr_psoc *psoc)
{
	struct nan_psoc_priv_obj *nan_obj = cfg_nan_get_priv_obj(psoc);

	if (!nan_obj) {
		nan_err("NAN obj null");
		return false;
	}
	return nan_obj->cfg_param.dp_enable;
}

uint32_t cfg_nan_get_ndi_channel(struct wlan_objmgr_psoc *psoc)
{
	struct nan_psoc_priv_obj *nan_obj = cfg_nan_get_priv_obj(psoc);

	if (!nan_obj) {
		nan_err("NAN obj null");
		return 0;
	}
	return nan_obj->cfg_param.ndi_ch;
}

bool cfg_nan_get_ndi_mac_randomize(struct wlan_objmgr_psoc *psoc)
{
	struct nan_psoc_priv_obj *nan_obj = cfg_nan_get_priv_obj(psoc);

	if (!nan_obj) {
		nan_err("NAN obj null");
		return false;
	}
	return nan_obj->cfg_param.ndi_mac_randomize;
}
