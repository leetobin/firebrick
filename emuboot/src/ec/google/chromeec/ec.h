/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2012 The Chromium OS Authors. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Mailbox EC communication interface for Google Chrome Embedded Controller.
 */

#ifndef _EC_GOOGLE_CHROMEEC_EC_H
#define _EC_GOOGLE_CHROMEEC_EC_H

#ifndef __PRE_RAM__
u32 google_chromeec_get_wake_mask(void);
int google_chromeec_set_sci_mask(u32 mask);
int google_chromeec_set_smi_mask(u32 mask);
int google_chromeec_set_wake_mask(u32 mask);
u8 google_chromeec_get_event(void);
int google_ec_running_ro(void);
u16 google_chromeec_get_board_version(void);
#endif

u32 google_chromeec_get_events_b(void);
int google_chromeec_kbbacklight(int percent);
void google_chromeec_post(u8 postcode);
void google_chromeec_log_events(u32 mask);

enum usb_charge_mode {
	USB_CHARGE_MODE_DISABLED,
	USB_CHARGE_MODE_CHARGE_AUTO,
	USB_CHARGE_MODE_CHARGE_BC12,
	USB_CHARGE_MODE_DOWNSTREAM_500MA,
	USB_CHARGE_MODE_DOWNSTREAM_1500MA,
};
int google_chromeec_set_usb_charge_mode(u8 port_id, enum usb_charge_mode mode);

#endif /* _EC_GOOGLE_CHROMEEC_EC_H */
