/*
 * Copyright (C) 2008 Google, Inc.
 * Copyright (c) 2008-2011, Code Aurora Forum. All rights reserved.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/gpio.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/clkdev.h>
#include <linux/dma-mapping.h>


#include <mach/irqs.h>
#include <mach/msm_iomap.h>
#include <mach/dma.h>
#include <mach/board.h>

#include "devices.h"

#include <asm/mach/flash.h>

#include <mach/mmc.h>
#include "clock-pcom.h"

static struct resource resources_uart1[] = {
        {
                .start  = INT_UART1,
                .end    = INT_UART1,
                .flags  = IORESOURCE_IRQ,
        },
        {
                .start  = MSM_UART1_PHYS,
                .end    = MSM_UART1_PHYS + MSM_UART1_SIZE - 1,
                .flags  = IORESOURCE_MEM,
        },
};

static struct resource resources_uart2[] = {
        {
                .start  = INT_UART2,
                .end    = INT_UART2,
                .flags  = IORESOURCE_IRQ,
        },
        {
                .start  = MSM_UART2_PHYS,
                .end    = MSM_UART2_PHYS + MSM_UART2_SIZE - 1,
                .flags  = IORESOURCE_MEM,
        },
};
static struct resource resources_uart3[] = {
	{
		.start	= INT_UART3,
		.end	= INT_UART3,
		.flags	= IORESOURCE_IRQ,
	},
	{
		.start	= MSM_UART3_PHYS,
		.end	= MSM_UART3_PHYS + MSM_UART3_SIZE - 1,
		.flags	= IORESOURCE_MEM,
		.name  = "uart_resource"
	},
};

struct platform_device msm_device_uart1 = {
        .name   = "msm_serial",
        .id     = 0,
        .num_resources  = ARRAY_SIZE(resources_uart1),
        .resource       = resources_uart1,
};

struct platform_device msm_device_uart2 = {
        .name   = "msm_serial",
        .id     = 1,
        .num_resources  = ARRAY_SIZE(resources_uart2),
        .resource       = resources_uart2,
};

struct platform_device msm_device_uart3 = {
	.name	= "msm_serial",
	.id	= 2,
	.num_resources	= ARRAY_SIZE(resources_uart3),
	.resource	= resources_uart3,
};

static struct resource msm_uart1_dm_resources[] = {
        {
                .start = MSM_UART1DM_PHYS,
                .end   = MSM_UART1DM_PHYS + PAGE_SIZE - 1,
                .flags = IORESOURCE_MEM,
        },
        {
                .start = INT_UART1DM_IRQ,
                .end   = INT_UART1DM_IRQ,
                .flags = IORESOURCE_IRQ,
        },
        {
                .start = INT_UART1DM_RX,
                .end   = INT_UART1DM_RX,
                .flags = IORESOURCE_IRQ,
        },
        {
                .start = DMOV_HSUART1_TX_CHAN,
                .end   = DMOV_HSUART1_RX_CHAN,
                .name  = "uartdm_channels",
                .flags = IORESOURCE_DMA,
        },
        {
                .start = DMOV_HSUART1_TX_CRCI,
                .end   = DMOV_HSUART1_RX_CRCI,
                .name  = "uartdm_crci",
                .flags = IORESOURCE_DMA,
        },
};

static u64 msm_uart_dm1_dma_mask = DMA_BIT_MASK(32);

struct platform_device msm_device_uart_dm1 = {
        .name = "msm_serial_hs",
        .id = 0,
        .num_resources = ARRAY_SIZE(msm_uart1_dm_resources),
        .resource = msm_uart1_dm_resources,
        .dev            = {
                .dma_mask = &msm_uart_dm1_dma_mask,
                .coherent_dma_mask = DMA_BIT_MASK(32),
        },
};

static struct resource msm_uart2_dm_resources[] = {
        {
                .start = MSM_UART2DM_PHYS,
                .end   = MSM_UART2DM_PHYS + PAGE_SIZE - 1,
                .flags = IORESOURCE_MEM,
        },
        {
                .start = INT_UART2DM_IRQ,
                .end   = INT_UART2DM_IRQ,
                .flags = IORESOURCE_IRQ,
        },
        {
                .start = INT_UART2DM_RX,
                .end   = INT_UART2DM_RX,
                .flags = IORESOURCE_IRQ,
        },
        {
                .start = DMOV_HSUART2_TX_CHAN,
                .end   = DMOV_HSUART2_RX_CHAN,
                .name  = "uartdm_channels",
                .flags = IORESOURCE_DMA,
        },
        {
                .start = DMOV_HSUART2_TX_CRCI,
                .end   = DMOV_HSUART2_RX_CRCI,
                .name  = "uartdm_crci",
                .flags = IORESOURCE_DMA,
        },
};

static u64 msm_uart_dm2_dma_mask = DMA_BIT_MASK(32);

struct platform_device msm_device_uart_dm2 = {
        .name = "msm_serial_hs",
        .id = 1,
        .num_resources = ARRAY_SIZE(msm_uart2_dm_resources),
        .resource = msm_uart2_dm_resources,
        .dev            = {
                .dma_mask = &msm_uart_dm2_dma_mask,
                .coherent_dma_mask = DMA_BIT_MASK(32),
        },
};

struct platform_device msm_device_smd = {
	.name   = "msm_smd",
	.id     = -1,
};

static struct resource resources_nand[] = {
        [0] = {
                .start  = 7,
                .end    = 7,
                .flags  = IORESOURCE_DMA,
        },
};

struct flash_platform_data msm_nand_data = {
        .parts          = NULL,
        .nr_parts       = 0,
};

struct platform_device msm_device_nand = {
        .name           = "msm_nand",
        .id             = -1,
        .num_resources  = ARRAY_SIZE(resources_nand),
        .resource       = resources_nand,
        .dev            = {
                .platform_data  = &msm_nand_data,
        },
};

static struct resource resources_otg[] = {
	{
		.start	= MSM_HSUSB_PHYS,
		.end	= MSM_HSUSB_PHYS + MSM_HSUSB_SIZE,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= INT_USB_HS,
		.end	= INT_USB_HS,
		.flags	= IORESOURCE_IRQ,
	},
};

struct platform_device msm_device_otg = {
	.name		= "msm_otg",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(resources_otg),
	.resource	= resources_otg,
	.dev		= {
		.coherent_dma_mask	= 0xffffffff,
	},
};

static struct resource resources_hsusb[] = {
	{
		.start	= MSM_HSUSB_PHYS,
		.end	= MSM_HSUSB_PHYS + MSM_HSUSB_SIZE,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= INT_USB_HS,
		.end	= INT_USB_HS,
		.flags	= IORESOURCE_IRQ,
	},
};

struct platform_device msm_device_hsusb = {
	.name		= "msm_hsusb",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(resources_hsusb),
	.resource	= resources_hsusb,
	.dev		= {
		.coherent_dma_mask	= 0xffffffff,
	},
};

static u64 dma_mask = 0xffffffffULL;
static struct resource resources_hsusb_host[] = {
	{
		.start	= MSM_HSUSB_PHYS,
		.end	= MSM_HSUSB_PHYS + MSM_HSUSB_SIZE,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= INT_USB_HS,
		.end	= INT_USB_HS,
		.flags	= IORESOURCE_IRQ,
	},
};

struct platform_device msm_device_hsusb_host = {
	.name		= "msm_hsusb_host",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(resources_hsusb_host),
	.resource	= resources_hsusb_host,
	.dev		= {
		.dma_mask               = &dma_mask,
		.coherent_dma_mask      = 0xffffffffULL,
	},
};

static struct resource resources_sdc1[] = {
	{
		.start	= MSM_SDC1_PHYS,
		.end	= MSM_SDC1_PHYS + MSM_SDC1_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= INT_SDC1_0,
		.end	= INT_SDC1_0,
		.flags	= IORESOURCE_IRQ,
		.name	= "cmd_irq",
	},
	{
		.start	= INT_SDC1_1,
		.end	= INT_SDC1_1,
		.flags	= IORESOURCE_IRQ,
		.name	= "pio_irq",
	},
	{
		.flags	= IORESOURCE_IRQ | IORESOURCE_DISABLED,
		.name	= "status_irq"
	},
	{
		.start	= 8,
		.end	= 8,
		.flags	= IORESOURCE_DMA,
	},
};

static struct resource resources_sdc2[] = {
	{
		.start	= MSM_SDC2_PHYS,
		.end	= MSM_SDC2_PHYS + MSM_SDC2_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= INT_SDC2_0,
		.end	= INT_SDC2_0,
		.flags	= IORESOURCE_IRQ,
		.name	= "cmd_irq",
	},
		{
		.start	= INT_SDC2_1,
		.end	= INT_SDC2_1,
		.flags	= IORESOURCE_IRQ,
		.name	= "pio_irq",
	},
	{
		.flags	= IORESOURCE_IRQ | IORESOURCE_DISABLED,
		.name	= "status_irq"
	},
	{
		.start	= 8,
		.end	= 8,
		.flags	= IORESOURCE_DMA,
	},
};

static struct resource resources_sdc3[] = {
	{
		.start	= MSM_SDC3_PHYS,
		.end	= MSM_SDC3_PHYS + MSM_SDC3_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= INT_SDC3_0,
		.end	= INT_SDC3_0,
		.flags	= IORESOURCE_IRQ,
		.name	= "cmd_irq",
	},
		{
		.start	= INT_SDC3_1,
		.end	= INT_SDC3_1,
		.flags	= IORESOURCE_IRQ,
		.name	= "pio_irq",
	},
	{
		.flags	= IORESOURCE_IRQ | IORESOURCE_DISABLED,
		.name	= "status_irq"
	},
	{
		.start	= 8,
		.end	= 8,
		.flags	= IORESOURCE_DMA,
	},
};

static struct resource resources_sdc4[] = {
	{
		.start	= MSM_SDC4_PHYS,
		.end	= MSM_SDC4_PHYS + MSM_SDC4_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= INT_SDC4_0,
		.end	= INT_SDC4_0,
		.flags	= IORESOURCE_IRQ,
		.name	= "cmd_irq",
	},
		{
		.start	= INT_SDC4_1,
		.end	= INT_SDC4_1,
		.flags	= IORESOURCE_IRQ,
		.name	= "pio_irq",
	},
	{
		.flags	= IORESOURCE_IRQ | IORESOURCE_DISABLED,
		.name	= "status_irq"
	},
	{
		.start	= 8,
		.end	= 8,
		.flags	= IORESOURCE_DMA,
	},
};

struct platform_device msm_device_sdc1 = {
	.name		= "msm_sdcc",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(resources_sdc1),
	.resource	= resources_sdc1,
	.dev		= {
		.coherent_dma_mask	= 0xffffffff,
	},
};

struct platform_device msm_device_sdc2 = {
	.name		= "msm_sdcc",
	.id		= 2,
	.num_resources	= ARRAY_SIZE(resources_sdc2),
	.resource	= resources_sdc2,
	.dev		= {
		.coherent_dma_mask	= 0xffffffff,
	},
};

struct platform_device msm_device_sdc3 = {
	.name		= "msm_sdcc",
	.id		= 3,
	.num_resources	= ARRAY_SIZE(resources_sdc3),
	.resource	= resources_sdc3,
	.dev		= {
		.coherent_dma_mask	= 0xffffffff,
	},
};

struct platform_device msm_device_sdc4 = {
	.name		= "msm_sdcc",
	.id		= 4,
	.num_resources	= ARRAY_SIZE(resources_sdc4),
	.resource	= resources_sdc4,
	.dev		= {
		.coherent_dma_mask	= 0xffffffff,
	},
};

#if defined(CONFIG_FB_MSM_MDP40)
#define MDP_BASE          0xA3F00000
#define PMDH_BASE         0xAD600000
#define EMDH_BASE         0xAD700000
#define TVENC_BASE        0xAD400000
#else
#define MDP_BASE          0xAA200000
#define PMDH_BASE         0xAA600000
#define EMDH_BASE         0xAA700000
#define TVENC_BASE        0xAA400000
#endif

static struct resource msm_mdp_resources[] = {
        {
                .name   = "mdp",
                .start  = MDP_BASE,
                .end    = MDP_BASE + 0x000F0000 - 1,
                .flags  = IORESOURCE_MEM,
        },
        {
                .start  = INT_MDP,
                .end    = INT_MDP,
                .flags  = IORESOURCE_IRQ,
        },
};

struct platform_device msm_mdp_device = {
        .name   = "msm_mdp",
        .id     = 0,
        .num_resources  = ARRAY_SIZE(msm_mdp_resources),
        .resource       = msm_mdp_resources,
};


static struct platform_device *msm_sdcc_devices[] __initdata = {
	&msm_device_sdc1,
	&msm_device_sdc2,
	&msm_device_sdc3,
	&msm_device_sdc4,
};

int __init msm_add_sdcc(unsigned int controller,
			struct msm_mmc_platform_data *plat,
			unsigned int stat_irq, unsigned long stat_irq_flags)
{
	struct platform_device	*pdev;
	struct resource *res;

	if (controller < 1 || controller > 4)
		return -EINVAL;

	pdev = msm_sdcc_devices[controller-1];
	pdev->dev.platform_data = plat;

	res = platform_get_resource_byname(pdev, IORESOURCE_IRQ, "status_irq");
	if (!res)
		return -EINVAL;
	else if (stat_irq) {
		res->start = res->end = stat_irq;
		res->flags &= ~IORESOURCE_DISABLED;
		res->flags |= stat_irq_flags;
	}

	return platform_device_register(pdev);
}


static DEFINE_CLK_PCOM(adm_clk,                ADM_CLK,        CLKFLAG_SKIP_AUTO_OFF);
static DEFINE_CLK_PCOM(adsp_clk,        ADSP_CLK,        CLKFLAG_SKIP_AUTO_OFF);
static DEFINE_CLK_PCOM(ahb_m_clk,        AHB_M_CLK,        CLKFLAG_SKIP_AUTO_OFF);
static DEFINE_CLK_PCOM(ahb_s_clk,        AHB_S_CLK,        CLKFLAG_SKIP_AUTO_OFF);
static DEFINE_CLK_PCOM(cam_m_clk,        CAM_M_CLK,        CLKFLAG_SKIP_AUTO_OFF);
static DEFINE_CLK_PCOM(axi_rotator_clk,        AXI_ROTATOR_CLK, 0);
static DEFINE_CLK_PCOM(ce_clk,                CE_CLK,                CLKFLAG_SKIP_AUTO_OFF);
static DEFINE_CLK_PCOM(csi0_clk,        CSI0_CLK,        CLKFLAG_SKIP_AUTO_OFF);
static DEFINE_CLK_PCOM(csi0_p_clk,        CSI0_P_CLK,        CLKFLAG_SKIP_AUTO_OFF);
static DEFINE_CLK_PCOM(csi0_vfe_clk,        CSI0_VFE_CLK,        CLKFLAG_SKIP_AUTO_OFF);
static DEFINE_CLK_PCOM(csi1_clk,        CSI1_CLK,        CLKFLAG_SKIP_AUTO_OFF);
static DEFINE_CLK_PCOM(csi1_p_clk,        CSI1_P_CLK,        CLKFLAG_SKIP_AUTO_OFF);
static DEFINE_CLK_PCOM(csi1_vfe_clk,        CSI1_VFE_CLK,        CLKFLAG_SKIP_AUTO_OFF);

static struct pcom_clk dsi_byte_clk = {
        .id = P_DSI_BYTE_CLK,
        .c = {
                .ops = &clk_ops_pcom_ext_config,
                .dbg_name = "dsi_byte_clk",
                CLK_INIT(dsi_byte_clk.c),
        },
};

static struct pcom_clk dsi_clk = {
        .id = P_DSI_CLK,
        .c = {
                .ops = &clk_ops_pcom_ext_config,
                .dbg_name = "dsi_clk",
                CLK_INIT(dsi_clk.c),
        },
};

static struct pcom_clk dsi_esc_clk = {
        .id = P_DSI_ESC_CLK,
        .c = {
                .ops = &clk_ops_pcom_ext_config,
                .dbg_name = "dsi_esc_clk",
                CLK_INIT(dsi_esc_clk.c),
        },
};

static struct pcom_clk dsi_pixel_clk = {
        .id = P_DSI_PIXEL_CLK,
        .c = {
                .ops = &clk_ops_pcom_ext_config,
                .dbg_name = "dsi_pixel_clk",
                CLK_INIT(dsi_pixel_clk.c),
        },
};

#if defined(CONFIG_ARCH_MSM7X30)
#define GPIO_I2C_CLK 70
#define GPIO_I2C_DAT 71
#elif defined(CONFIG_ARCH_QSD8X50)
#define GPIO_I2C_CLK 95
#define GPIO_I2C_DAT 96
#else
#define GPIO_I2C_CLK 60
#define GPIO_I2C_DAT 61
#endif

void msm_i2c_gpio_init(void)
{
        gpio_request(GPIO_I2C_CLK, "i2c_clk");
        gpio_request(GPIO_I2C_DAT, "i2c_data");
}