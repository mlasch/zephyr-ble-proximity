/* main.c - Application main entry point */

/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <sys/printk.h>
#include <sys/util.h>
#include <devicetree.h>
#include <device.h>
#include <drivers/gpio.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>

/* Scan callback function. The result is filtered by the service uuid reserved
 * for the Exposure Notification Service.
 * Data send is send in little endian.
 */
static void scan_cb(const bt_addr_le_t *addr, s8_t rssi, u8_t adv_type,
		    struct net_buf_simple *buf)
{
	u32_t i;
	u16_t service_uuid = *(u16_t *) &buf->data[5];
	
	if (service_uuid == 0xfd6f)
	{
		printk("Got something! adv_type: %d rssi: %d, PKT: ", adv_type, rssi);
		for (i=0;i<buf->len;i++)
		{
			printk("%02x", buf->data[i]);
		}

		printk("\n");
	}
}

void main(void)
{
	/* scan paramters:
	 * - interval: N*0.625ms
	 * - window: N*0.625ms
	 */
	struct bt_le_scan_param scan_param = {
		.type       = BT_HCI_LE_SCAN_PASSIVE,
		.options    = BT_LE_SCAN_OPT_NONE,
		.interval   = 0x0100,
		.window     = 0x0080,
	};
	int err;

	printk("Starting Scanner/Advertiser Demo\n");

	/* Initialize the Bluetooth Subsystem */
	err = bt_enable(NULL);
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}

	printk("Bluetooth initialized\n");

	err = bt_le_scan_start(&scan_param, scan_cb);
	if (err) {
		printk("Starting scanning failed (err %d)\n", err);
		return;
	}
	
	do {
		k_sleep(K_MSEC(800));

	} while (1);
}
