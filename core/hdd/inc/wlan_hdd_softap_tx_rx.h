/*
 * Copyright (c) 2014-2015 The Linux Foundation. All rights reserved.
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

#if !defined(WLAN_HDD_SOFTAP_TX_RX_H)
#define WLAN_HDD_SOFTAP_TX_RX_H

/**
 * DOC: wlan_hdd_softap_tx_rx.h
 *
 *Linux HDD SOFTAP Tx/RX APIs
 */

#include <wlan_hdd_hostapd.h>

int hdd_softap_hard_start_xmit(struct sk_buff *skb,
			       struct net_device *dev);
void hdd_softap_tx_timeout(struct net_device *dev);
CDF_STATUS hdd_softap_init_tx_rx(hdd_adapter_t *pAdapter);
CDF_STATUS hdd_softap_deinit_tx_rx(hdd_adapter_t *pAdapter);
CDF_STATUS hdd_softap_init_tx_rx_sta(hdd_adapter_t *pAdapter,
				     uint8_t STAId,
				     struct cdf_mac_addr *pmacAddrSTA);
CDF_STATUS hdd_softap_deinit_tx_rx_sta(hdd_adapter_t *pAdapter,
				       uint8_t STAId);
CDF_STATUS hdd_softap_rx_packet_cbk(void *cds_context,
				    cdf_nbuf_t rxBufChain,
				    uint8_t staId);
#ifdef IPA_OFFLOAD
CDF_STATUS hdd_softap_rx_mul_packet_cbk(void *cds_context,
					cdf_nbuf_t rx_buf_list, uint8_t staId);
#endif /* IPA_OFFLOAD */

CDF_STATUS hdd_softap_deregister_sta(hdd_adapter_t *pAdapter,
				     uint8_t staId);
CDF_STATUS hdd_softap_register_sta(hdd_adapter_t *pAdapter,
				   bool fAuthRequired,
				   bool fPrivacyBit,
				   uint8_t staId,
				   uint8_t ucastSig,
				   uint8_t bcastSig,
				   struct cdf_mac_addr *pPeerMacAddress,
				   bool fWmmEnabled);
CDF_STATUS hdd_softap_register_bc_sta(hdd_adapter_t *pAdapter,
				      bool fPrivacyBit);
CDF_STATUS hdd_softap_deregister_bc_sta(hdd_adapter_t *pAdapter);
CDF_STATUS hdd_softap_stop_bss(hdd_adapter_t *pHostapdAdapter);
CDF_STATUS hdd_softap_change_sta_state(hdd_adapter_t *pAdapter,
				       struct cdf_mac_addr *pDestMacAddress,
				       enum ol_txrx_peer_state state);
CDF_STATUS hdd_softap_get_sta_id(hdd_adapter_t *pAdapter,
				 struct cdf_mac_addr *pMacAddress,
				 uint8_t *staId);

#ifdef QCA_LL_LEGACY_TX_FLOW_CONTROL
void hdd_softap_tx_resume_timer_expired_handler(void *adapter_context);
void hdd_softap_tx_resume_cb(void *adapter_context, bool tx_resume);
#else
static inline
void hdd_softap_tx_resume_timer_expired_handler(void *adapter_context)
{
	return;
}
static inline
void hdd_softap_tx_resume_cb(void *adapter_context, bool tx_resume)
{
	return;
}
#endif /* QCA_LL_LEGACY_TX_FLOW_CONTROL */

#endif /* end #if !defined(WLAN_HDD_SOFTAP_TX_RX_H) */
