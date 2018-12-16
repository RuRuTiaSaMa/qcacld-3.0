/*
 * Copyright (c) 2017-2018 The Linux Foundation. All rights reserved.
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
 * DOC: contains nan definitions exposed to other modules
 */

#ifndef _WLAN_NAN_API_H_
#define _WLAN_NAN_API_H_
#ifdef WLAN_FEATURE_NAN_CONVERGENCE

#include "wlan_objmgr_vdev_obj.h"
#include "wlan_objmgr_psoc_obj.h"
#include "qdf_status.h"
#include "../src/nan_main_i.h"

struct wlan_objmgr_psoc;

/**
 * nan_init: initializes NAN component, called by dispatcher init
 *
 * Return: status of operation
 */
QDF_STATUS nan_init(void);

/**
 * nan_deinit: de-initializes NAN component, called by dispatcher init
 *
 * Return: status of operation
 */
QDF_STATUS nan_deinit(void);

/**
 * nan_psoc_enable: psoc enable API for NANitioning component
 * @psoc: pointer to PSOC
 *
 * Return: status of operation
 */
QDF_STATUS nan_psoc_enable(struct wlan_objmgr_psoc *psoc);

/**
 * nan_psoc_disable: psoc disable API for NANitioning component
 * @psoc: pointer to PSOC
 *
 * Return: status of operation
 */
QDF_STATUS nan_psoc_disable(struct wlan_objmgr_psoc *psoc);

/**
 * nan_get_vdev_priv_obj: get NAN priv object from vdev object
 * @vdev: pointer to vdev object
 *
 * Return: pointer to NAN vdev private object
 */
static inline
struct nan_vdev_priv_obj *nan_get_vdev_priv_obj(struct wlan_objmgr_vdev *vdev)
{
	struct nan_vdev_priv_obj *obj;

	if (!vdev) {
		nan_err("vdev is null");
		return NULL;
	}
	obj = wlan_objmgr_vdev_get_comp_private_obj(vdev, WLAN_UMAC_COMP_NAN);

	return obj;
}

/**
 * nan_get_psoc_priv_obj: get NAN priv object from psoc object
 * @psoc: pointer to psoc object
 *
 * Return: pointer to NAN psoc private object
 */
static inline
struct nan_psoc_priv_obj *nan_get_psoc_priv_obj(struct wlan_objmgr_psoc *psoc)
{
	struct nan_psoc_priv_obj *obj;

	if (!psoc) {
		nan_err("psoc is null");
		return NULL;
	}
	obj = wlan_objmgr_psoc_get_comp_private_obj(psoc, WLAN_UMAC_COMP_NAN);

	return obj;
}

/**
 * nan_psoc_get_tx_ops: get TX ops from the NAN private object
 * @psoc: pointer to psoc object
 *
 * Return: pointer to TX op callback
 */
static inline
struct wlan_nan_tx_ops *nan_psoc_get_tx_ops(struct wlan_objmgr_psoc *psoc)
{
	struct nan_psoc_priv_obj *nan_priv;

	if (!psoc) {
		nan_err("psoc is null");
		return NULL;
	}

	nan_priv = nan_get_psoc_priv_obj(psoc);
	if (!nan_priv) {
		nan_err("psoc private object is null");
		return NULL;
	}

	return &nan_priv->tx_ops;
}

/**
 * nan_psoc_get_rx_ops: get RX ops from the NAN private object
 * @psoc: pointer to psoc object
 *
 * Return: pointer to RX op callback
 */
static inline
struct wlan_nan_rx_ops *nan_psoc_get_rx_ops(struct wlan_objmgr_psoc *psoc)
{
	struct nan_psoc_priv_obj *nan_priv;

	if (!psoc) {
		nan_err("psoc is null");
		return NULL;
	}

	nan_priv = nan_get_psoc_priv_obj(psoc);
	if (!nan_priv) {
		nan_err("psoc private object is null");
		return NULL;
	}

	return &nan_priv->rx_ops;
}
#else /* WLAN_FEATURE_NAN_CONVERGENCE */
static inline QDF_STATUS nan_init(void)
{
	return QDF_STATUS_SUCCESS;
}

static inline QDF_STATUS nan_deinit(void)
{
	return QDF_STATUS_SUCCESS;
}

static inline QDF_STATUS nan_psoc_enable(struct wlan_objmgr_psoc *psoc)
{
	return QDF_STATUS_SUCCESS;
}

static inline QDF_STATUS nan_psoc_disable(struct wlan_objmgr_psoc *psoc)
{
	return QDF_STATUS_SUCCESS;
}

#endif /* WLAN_FEATURE_NAN_CONVERGENCE */
#endif /* _WLAN_NAN_API_H_ */