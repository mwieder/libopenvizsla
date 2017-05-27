#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ftdi.h>

#include <cha.h>
#include <chb.h>

#define OV_VENDOR  0x1d50
#define OV_PRODUCT 0x607c

#define PORTB_DONE_BIT     (1 << 2)  // GPIOH2
#define PORTB_INIT_BIT     (1 << 5)  // GPIOH5

int main(int argc, char** argv) {
	unsigned char buf[] = {0x55, 0x04, 0x01, 0x00, 0x5a};
	unsigned char inp_buf[4096];
	int ret;

	struct cha cha;
	struct chb chb;

	struct ftdi_version_info version;

	ret = cha_init(&cha);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}

	ret = chb_init(&chb);
	if (ret == -1) {
		fprintf(stderr, chb_get_error_string(&chb));
		return 1;
	}

	ret = cha_open(&cha);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}

	ret = chb_open(&chb);
	if (ret == -1) {
		fprintf(stderr, chb_get_error_string(&chb));
		return 1;
	}

	uint8_t status;

	ret = chb_set_high(&chb, 0);
	if (ret == -1) {
		fprintf(stderr, chb_get_error_string(&chb));
		return 1;
	}

	ret = chb_get_high(&chb, &status);
	if (ret == -1) {
		fprintf(stderr, chb_get_error_string(&chb));
		return 1;
	}

	printf("%x %d %d\n", status, status & PORTB_INIT_BIT, status & PORTB_DONE_BIT);

	ret = cha_switch_fifo_mode(&cha);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}

	/* All leds on */
	// dev.regs.SDRAM_SINK_GO.wr(0)
	ret = cha_write_reg(&cha, 0xe11, 0x0);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	// dev.regs.SDRAM_HOST_READ_GO.wr(0)
	ret = cha_write_reg(&cha, 0xc28, 0x0);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	// dev.regs.SDRAM_SINK_RING_BASE.wr(ring_base)
	ret = cha_write_reg(&cha, 0xe09, 0x0);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	ret = cha_write_reg(&cha, 0xe0a, 0x0);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	ret = cha_write_reg(&cha, 0xe0b, 0x0);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	ret = cha_write_reg(&cha, 0xe0c, 0x0);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	// dev.regs.SDRAM_SINK_RING_END.wr(ring_end)
	ret = cha_write_reg(&cha, 0xe0d, 0x1);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	ret = cha_write_reg(&cha, 0xe0e, 0x0);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	ret = cha_write_reg(&cha, 0xe0f, 0x0);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	ret = cha_write_reg(&cha, 0xe10, 0x0);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	// dev.regs.SDRAM_HOST_READ_RING_BASE.wr(ring_base)
	ret = cha_write_reg(&cha, 0xc1c, 0x0);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	ret = cha_write_reg(&cha, 0xc1d, 0x0);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	ret = cha_write_reg(&cha, 0xc1e, 0x0);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	ret = cha_write_reg(&cha, 0xc1f, 0x0);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	// dev.regs.SDRAM_HOST_READ_RING_END.wr(ring_end)
	ret = cha_write_reg(&cha, 0xc20, 0x1);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	ret = cha_write_reg(&cha, 0xc21, 0x0);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	ret = cha_write_reg(&cha, 0xc22, 0x0);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	ret = cha_write_reg(&cha, 0xc23, 0x0);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	// dev.regs.SDRAM_SINK_GO.wr(1)
	ret = cha_write_reg(&cha, 0xe11, 0x01);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	// dev.regs.SDRAM_HOST_READ_GO.wr(1)
	ret = cha_write_reg(&cha, 0xc28, 0x01);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}

	// dev.ulpiregs.func_ctl.wr(0x4a)
	// self.regs.ucfg_wdata.wr(value)
	ret = cha_write_reg(&cha, 0x402, 0x4a);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}
	// self.regs.ucfg_wcmd.wr(UCFG_REG_GO | (addr & UCFG_REG_ADDRMASK))
	ret = cha_write_reg(&cha, 0x403, 0x80 | (0x04 & 0x3F));
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}

	// dev.regs.CSTREAM_CFG.wr(1)
	ret = cha_write_reg(&cha, 0x800, 0x01);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}

	// dev.regs.SDRAM_SINK_PTR_READ.wr(0)
	ret = cha_write_reg(&cha, 0xe00, 0x00);
	if (ret == -1) {
		fprintf(stderr, cha_get_error_string(&cha));
		return 1;
	}


	while (1) {
		struct ftdi_transfer_control* ctl = ftdi_read_data_submit(&cha.ftdi, inp_buf, 4096);

		if (ftdi_transfer_data_done(ctl) < 0) {
			fprintf(stderr, ftdi_get_error_string(&cha.ftdi));
			return 1;
		}
		printf("%d %d .\n", ctl->size, ctl->offset);
	}

	chb_destroy(&chb);
	cha_destroy(&cha);

	return 0;
}
