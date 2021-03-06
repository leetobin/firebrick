/* $NoKeywords:$ */
/**
 * @file
 *
 * Initialize GFX configuration data structure.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 64730 $   @e \$Date: 2012-01-30 02:05:39 -0600 (Mon, 30 Jan 2012) $
 *
 */
/*
*****************************************************************************
*
* Copyright 2008 - 2012 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
*
* AMD is granting you permission to use this software (the Materials)
* pursuant to the terms and conditions of your Software License Agreement
* with AMD.  This header does *NOT* give you permission to use the Materials
* or any rights under AMD's intellectual property.  Your use of any portion
* of these Materials shall constitute your acceptance of those terms and
* conditions.  If you do not agree to the terms and conditions of the Software
* License Agreement, please do not use any portion of these Materials.
*
* CONFIDENTIALITY:  The Materials and all other information, identified as
* confidential and provided to you by AMD shall be kept confidential in
* accordance with the terms and conditions of the Software License Agreement.
*
* LIMITATION OF LIABILITY: THE MATERIALS AND ANY OTHER RELATED INFORMATION
* PROVIDED TO YOU BY AMD ARE PROVIDED "AS IS" WITHOUT ANY EXPRESS OR IMPLIED
* WARRANTY OF ANY KIND, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
* MERCHANTABILITY, NONINFRINGEMENT, TITLE, FITNESS FOR ANY PARTICULAR PURPOSE,
* OR WARRANTIES ARISING FROM CONDUCT, COURSE OF DEALING, OR USAGE OF TRADE.
* IN NO EVENT SHALL AMD OR ITS LICENSORS BE LIABLE FOR ANY DAMAGES WHATSOEVER
* (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF PROFITS, BUSINESS
* INTERRUPTION, OR LOSS OF INFORMATION) ARISING OUT OF AMD'S NEGLIGENCE,
* GROSS NEGLIGENCE, THE USE OF OR INABILITY TO USE THE MATERIALS OR ANY OTHER
* RELATED INFORMATION PROVIDED TO YOU BY AMD, EVEN IF AMD HAS BEEN ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGES.  BECAUSE SOME JURISDICTIONS PROHIBIT THE
* EXCLUSION OR LIMITATION OF LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES,
* THE ABOVE LIMITATION MAY NOT APPLY TO YOU.
*
* AMD does not assume any responsibility for any errors which may appear in
* the Materials or any other related information provided to you by AMD, or
* result from use of the Materials or any related information.
*
* You agree that you will not reverse engineer or decompile the Materials.
*
* NO SUPPORT OBLIGATION: AMD is not obligated to furnish, support, or make any
* further information, software, technical information, know-how, or show-how
* available to you.  Additionally, AMD retains the right to modify the
* Materials at any time, without notice, and is not obligated to provide such
* modified Materials to you.
*
* U.S. GOVERNMENT RESTRICTED RIGHTS: The Materials are provided with
* "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
* subject to the restrictions as set forth in FAR 52.227-14 and
* DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
* Government constitutes acknowledgement of AMD's proprietary rights in them.
*
* EXPORT ASSURANCE:  You agree and certify that neither the Materials, nor any
* direct product thereof will be exported directly or indirectly, into any
* country prohibited by the United States Export Administration Act and the
* regulations thereunder, without the required authorization from the U.S.
* government nor will be used for any purpose prohibited by the same.
* ***************************************************************************
*
*/

#ifndef _GNBGFX_H_
#define _GNBGFX_H_

//#ifndef PVOID
//  typedef UINT64 PVOID;
//#endif

#define DEVICE_DFP                                0x1
#define DEVICE_CRT                                0x2
#define DEVICE_LCD                                0x3


#define CONNECTOR_DISPLAYPORT_ENUM                0x3013
#define CONNECTOR_HDMI_TYPE_A_ENUM                0x300c
#define CONNECTOR_SINGLE_LINK_DVI_D_ENUM          0x3003
#define CONNECTOR_DUAL_LINK_DVI_D_ENUM            0x3004
#define CONNECTOR_SINGLE_LINK_DVI_I_ENUM          0x3001
#define CONNECTOR_DUAL_LINK_DVI_I_ENUM            0x3002
#define CONNECTOR_VGA_ENUM                        0x3005
#define CONNECTOR_LVDS_ENUM                       0x300E
#define CONNECTOR_eDP_ENUM                        0x3014
#define CONNECTOR_LVDS_eDP_ENUM                   0x3016
#define ENCODER_TRAVIS_ENUM_ID1                   0x2123
#define ENCODER_TRAVIS_ENUM_ID2                   0x2223
#define ENCODER_ALMOND_ENUM_ID1                   0x2122
#define ENCODER_NOT_PRESENT                       0x0000

// no eDP->LVDS translator chip
#define eDP_TO_LVDS_RX_DISABLE                    0x00
// common eDP->LVDS translator chip without AMD SW init
#define eDP_TO_LVDS_COMMON_ID                     0x01
// Realtek tansaltor which require AMD SW init
#define eDP_TO_LVDS_REALTEK_ID                    0x02


#define ATOM_DEVICE_CRT1_SUPPORT                  0x0001
#define ATOM_DEVICE_DFP1_SUPPORT                  0x0008
#define ATOM_DEVICE_DFP6_SUPPORT                  0x0040
#define ATOM_DEVICE_DFP2_SUPPORT                  0x0080
#define ATOM_DEVICE_DFP3_SUPPORT                  0x0200
#define ATOM_DEVICE_DFP4_SUPPORT                  0x0400
#define ATOM_DEVICE_DFP5_SUPPORT                  0x0800
#define ATOM_DEVICE_LCD1_SUPPORT                  0x0002

/// Graphics card information structure
typedef struct {
  UINT32   AmdPcieGfxCardBitmap;                  ///< AMD PCIE graphics card information
  UINT32   PcieGfxCardBitmap;                     ///< All PCIE graphics card information
  UINT32   PciGfxCardBitmap;                      ///< All PCI graphics card information
} GFX_CARD_CARD_INFO;

typedef enum {
  iGpuVgaAdapter,                                       ///< Configure iGPU as VGA adapter
  iGpuVgaNonAdapter                                     ///< Configure iGPU as non VGA adapter
} GFX_IGPU_VGA_MODE;

typedef enum {
  excel992,
  excel993
} UMA_STEERING;

/// User Options
typedef enum {
  OptionDisabled,                                       ///< Disabled
  OptionEnabled                                         ///< Enabled
} CONTROL_OPTION;

/// GFX enable Policy
typedef enum {
  GmcPowerGatingDisabled,                               ///< Disable Power gating
  GmcPowerGatingStutterOnly,                            ///< GMC Stutter Only mode
  GmcPowerGatingWidthStutter                            ///< GMC Power gating with Stutter mode
} GMC_POWER_GATING;

/// Internal GFX mode
typedef enum {
  GfxControllerLegacyBridgeMode,                        ///< APC bridge Legacy mode
  GfxControllerPcieEndpointMode,                        ///< IGFX PCIE Bus 0, Device 1
} GFX_CONTROLLER_MODE;

/// Graphics Platform Configuration
typedef struct {
  UINT32                       StdHeader;                ///< Standard Header TODO: Used to be PVOID
  PCI_ADDR                    GfxPciAddress;            ///< Graphics PCI Address
  UMA_INFO                    UmaInfo;                  ///< UMA Information
  UINT32                      GmmBase;                  ///< GMM Base
  UINT8                       GnbHdAudio;               ///< Control GFX HD Audio controller(Used for HDMI and DP display output),
                                                        ///< essentially it enables function 1 of graphics device.
                                                        ///< @li 0 = HD Audio disable
                                                        ///< @li 1 = HD Audio enable
  UINT8                       AbmSupport;               ///< Automatic adjust LVDS/eDP Back light level support.It is
                                                        ///< characteristic specific to display panel which used by platform design.
                                                        ///< @li 0 = ABM support disabled
                                                        ///< @li 1 = ABM support enabled
  UINT8                       DynamicRefreshRate;       ///< Adjust refresh rate on LVDS/eDP.
  UINT16                      LcdBackLightControl;      ///< The PWM frequency to LCD backlight control.
                                                        ///< If equal to 0 backlight not controlled by iGPU.
  UINT32                      AmdPlatformType;          ///< Platform type
  UMA_STEERING                UmaSteering;              ///< UMA Steering
  GFX_IGPU_VGA_MODE           iGpuVgaMode;              ///< iGPU VGA mode
  BOOLEAN                     GmcClockGating;           ///< Clock gating
  BOOLEAN                     GmcLockRegisters;         ///< GmcLock Registers
  BOOLEAN                     GfxFusedOff;              ///< Record if GFX is fused off.
  GMC_POWER_GATING            GmcPowerGating;           ///< Gmc Power Gating.
  UINT8                       Gnb3dStereoPinIndex;      ///< 3D Stereo Pin ID
  GFX_CONTROLLER_MODE         GfxControllerMode;        ///< Gfx controller mode
  UINT16                      LvdsSpreadSpectrum;       ///< Spread spectrum value in 0.01 %
  UINT16                      LvdsSpreadSpectrumRate;   ///< Spread spectrum frequency used by SS hardware logic in unit of 10Hz, 0 - default frequency 40kHz
  UINT8                       LvdsPowerOnSeqDigonToDe;    ///< Panel initialization timing.
  UINT8                       LvdsPowerOnSeqDeToVaryBl;   ///< Panel initialization timing.
  UINT8                       LvdsPowerOnSeqDeToDigon;    ///< Panel initialization timing.
  UINT8                       LvdsPowerOnSeqVaryBlToDe;   ///< Panel initialization timing.
  UINT8                       LvdsPowerOnSeqOnToOffDelay; ///< Panel initialization timing.
  UINT8                       LvdsPowerOnSeqVaryBlToBlon; ///< Panel initialization timing.
  UINT8                       LvdsPowerOnSeqBlonToVaryBl; ///< Panel initialization timing.
  UINT16                      LvdsMaxPixelClockFreq;      ///< The maximum pixel clock frequency supported.
  UINT32                      LcdBitDepthControlValue;    ///< The LCD bit depth control settings.
  UINT8                       Lvds24bbpPanelMode;         ///< The LVDS 24 BBP mode.
  LVDS_MISC_CONTROL           LvdsMiscControl;            ///< THe LVDS swap/Hsync/Vsync/BLON/Volt-overwrite control
  GFX_CARD_CARD_INFO          GfxDiscreteCardInfo;        ///< Discrete GFX card info
  UINT16                      PcieRefClkSpreadSpectrum;   ///< Spread spectrum value in 0.01 %
  BOOLEAN                     GnbRemoteDisplaySupport;    ///< Wireless Display Enable
  UINT8                       gfxplmcfg0 ;
  DISPLAY_MISC_CONTROL        DisplayMiscControl;         ///< The Display misc control
} GFX_PLATFORM_CONFIG;


typedef UINT32 ULONG;
typedef UINT16 USHORT;
typedef UINT8  UCHAR;

/// Driver interface header structure
typedef struct _ATOM_COMMON_TABLE_HEADER {
  USHORT                      usStructureSize;             ///< Structure size
  UCHAR                       ucTableFormatRevision;       ///< Format revision number
  UCHAR                       ucTableContentRevision;      ///< Contents revision number
} ATOM_COMMON_TABLE_HEADER;

/// Link ping mapping for DP/eDP/LVDS
typedef struct _ATOM_DP_CONN_CHANNEL_MAPPING {
  UCHAR ucDP_Lane0_Source  :2;                      ///< Define which pin connect to DP connector DP_Lane0, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
  UCHAR ucDP_Lane1_Source  :2;                      ///< Define which pin connect to DP connector DP_Lane1, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
  UCHAR ucDP_Lane2_Source  :2;                      ///< Define which pin connect to DP connector DP_Lane2, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
  UCHAR ucDP_Lane3_Source  :2;                      ///< Define which pin connect to DP connector DP_Lane3, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
} ATOM_DP_CONN_CHANNEL_MAPPING;

/// Link ping mapping for DVI/HDMI
typedef struct _ATOM_DVI_CONN_CHANNEL_MAPPING {
  UCHAR ucDVI_DATA2_Source  :2;                     ///< Define which pin connect to DVI connector data Lane2, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
  UCHAR ucDVI_DATA1_Source  :2;                     ///< Define which pin connect to DVI connector data Lane1, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
  UCHAR ucDVI_DATA0_Source  :2;                     ///< Define which pin connect to DVI connector data Lane0, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
  UCHAR ucDVI_CLK_Source    :2;                     ///< Define which pin connect to DVI connector clock lane, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
} ATOM_DVI_CONN_CHANNEL_MAPPING;


/// External Display Path
typedef struct _EXT_DISPLAY_PATH {
  USHORT                      usDeviceTag;          ///< A bit vector to show what devices are supported
  USHORT                      usDeviceACPIEnum;     ///< 16bit device ACPI id.
  USHORT                      usDeviceConnector;    ///< A physical connector for displays to plug in, using object connector definitions
  UCHAR                       ucExtAUXDDCLutIndex;  ///< An index into external AUX/DDC channel LUT
  UCHAR                       ucExtHPDPINLutIndex;  ///< An index into external HPD pin LUT
  USHORT                      usExtEncoderObjId;    ///< external encoder object id
  union {                                           ///< Lane mapping
    UCHAR                     ucChannelMapping;     ///< lane mapping on connector (ucChannelMapping=0 use default)
    ATOM_DP_CONN_CHANNEL_MAPPING  asDPMapping;      ///< lane mapping on connector (ucChannelMapping=0 use default)
    ATOM_DVI_CONN_CHANNEL_MAPPING asDVIMapping;     ///< lane mapping on connector (ucChannelMapping=0 use default)
  } ChannelMapping;
  UCHAR                       ucChPNInvert;         ///< Bit vector for up to 8 lanes. 0: P and N is not invert, 1: P and N is inverted
  USHORT                      usCaps;               ///< Capabilities IF BIT[0] == 1, downgrade phy link to DP1.1
  USHORT                      usReserved;           ///< Reserved
} EXT_DISPLAY_PATH;

/// External Display Connection Information
typedef  struct _ATOM_EXTERNAL_DISPLAY_CONNECTION_INFO {
  ATOM_COMMON_TABLE_HEADER    sHeader;              ///< Standard Header
  UCHAR                       ucGuid [16];          ///< Guid
  EXT_DISPLAY_PATH            sPath[7];             ///< External Display Path
  UCHAR                       ucChecksum;           ///< Checksum
  UCHAR                       uc3DStereoPinId;      ///< 3D Stereo Pin ID
  UCHAR                       ucRemoteDisplayConfig;   ///< Bit0=1:Enable Wireless Display through APU VCE HW function
  UCHAR                       uceDPToLVDSRxId;      ///< 3rd party eDP to LVDS translator chip presented. 0:no, 1:chip without AMD SW init, 2:Realtek tansaltor which require AMD SW init
  UCHAR                       Reserved [4];         ///< Reserved
} ATOM_EXTERNAL_DISPLAY_CONNECTION_INFO;

/// Displclk to VID relation table
typedef struct _ATOM_CLK_VOLT_CAPABILITY {
  ULONG                       ulVoltageIndex;       ///< The Voltage Index indicated by FUSE, same voltage index shared with SCLK DPM fuse table
  ULONG                       ulMaximumSupportedCLK;///< Maximum clock supported with specified voltage index, unit in 10kHz
} ATOM_CLK_VOLT_CAPABILITY;

/// Available Sclk table
typedef struct _ATOM_AVAILABLE_SCLK_LIST {
  ULONG                        ulSupportedSCLK;     ///< Maximum clock supported with specified voltage index,  unit in 10kHz
  USHORT                       usVoltageIndex;      ///< The Voltage Index indicated by FUSE for specified SCLK
  USHORT                       usVoltageID;         ///< The Voltage ID indicated by FUSE for specified SCLK
} ATOM_AVAILABLE_SCLK_LIST;

/// Integrate System Info Table is used for Llano/Ontario APU
typedef struct _ATOM_INTEGRATED_SYSTEM_INFO_V6 {
  ATOM_COMMON_TABLE_HEADER    sHeader;                       ///< Standard Header
  ULONG                       ulBootUpEngineClock;           ///< VBIOS bootup Engine clock frequency, in 10kHz unit.
  ULONG                       excel994;
  ULONG                       ulBootUpUMAClock;              ///< System memory boot up clock frequency in 10Khz unit.
  ATOM_CLK_VOLT_CAPABILITY    sDISPCLK_Voltage[4];           ///< Report Display clock voltage requirement.
  ULONG                       ulBootUpReqDisplayVector;      /**< VBIOS boot up display IDs, following are supported devices in Llano/Fam 12 and Ontario/Fam 14 projects:
                                                               * ATOM_DEVICE_CRT1_SUPPORT                  0x0001
                                                               * ATOM_DEVICE_CRT2_SUPPORT                  0x0010
                                                               * ATOM_DEVICE_DFP1_SUPPORT                  0x0008
                                                               * ATOM_DEVICE_DFP6_SUPPORT                  0x0040
                                                               * ATOM_DEVICE_DFP2_SUPPORT                  0x0080
                                                               * ATOM_DEVICE_DFP3_SUPPORT                  0x0200
                                                               * ATOM_DEVICE_DFP4_SUPPORT                  0x0400
                                                               * ATOM_DEVICE_DFP5_SUPPORT                  0x0800
                                                               * ATOM_DEVICE_LCD1_SUPPORT                  0x0002
                                                               */
  ULONG                       ulOtherDisplayMisc;            ///< Other display related flags, not defined yet.
  ULONG                       ulGPUCapInfo;                  /**> @li BIT[0] - TMDS/HDMI Coherent Mode 0: use cascade PLL mode, 1: use signel PLL mode.
                                                               *  @li BIT[1] - DP mode 0: use cascade PLL mode, 1: use single PLL mode
                                                               *  @li BIT[3] - AUX HW mode detection logic 0: Enable, 1: Disable
                                                               */
  ULONG                       ulSB_MMIO_Base_Addr;           ///< Physical Base address to SB MMIO space. Driver need to initialize it for SMU usage.
  USHORT                      usRequestedPWMFreqInHz;        ///< Panel Required PWM frequency. if this parameter is 0 PWM from to control LCD Backlight will be disabled.
  UCHAR                       ucHtcTmpLmt;                   ///< HTC temperature limit.The processor enters HTC-active state when Tctl reaches or exceeds HtcHystLmt.
  UCHAR                       ucHtcHystLmt;                  ///< HTC hysteresis.The processor exits HTC-active state when Tctl is less than HtcTmpLmt minus HtcHystLmt.
  ULONG                       ulMinEngineClock;              ///< Min SCLK
  ULONG                       ulSystemConfig;                /**< System configuration
                                                               *  @li BIT[0] - 0: PCIE Power Gating Disabled, 1: PCIE Power Gating Enabled.
                                                               *  @li BIT[1] - 0: DDR-DLL shut-down feature disabled, 1: DDR-DLL shut-down feature enabled.
                                                               *  @li BIT[2] - 0: DDR-PLL Power down feature disabled, 1: DDR-PLL Power down feature enabled.
                                                               */
  ULONG                       ulCPUCapInfo;                  ///< TBD
  USHORT                      usNBP0Voltage;                 ///< VID for voltage on NB P0 State
  USHORT                      usNBP1Voltage;                 ///< VID for voltage on NB P1 State
  USHORT                      usBootUpNBVoltage;             ///< Voltage Index of GNB voltage configured by SBIOS, which is sufficient to support VBIOS DISPCLK requirement.
  USHORT                      usExtDispConnInfoOffset;       ///< Offset to sExtDispConnInfo inside the structure
  USHORT                      usPanelRefreshRateRange;       /**< Bit vector for LVDS/eDP supported refresh rate range. If DRR is enabled, 2 of the bits must be set.
                                                               * SUPPORTED_LCD_REFRESHRATE_30Hz          0x0004
                                                               * SUPPORTED_LCD_REFRESHRATE_40Hz          0x0008
                                                               * SUPPORTED_LCD_REFRESHRATE_50Hz          0x0010
                                                               * SUPPORTED_LCD_REFRESHRATE_60Hz          0x0020
                                                               */
  UCHAR                       ucMemoryType;                  ///< Memory type (3 for DDR3)
  UCHAR                       ucUMAChannelNumber;            ///< System memory channel numbers.
  ULONG                       ulCSR_M3_ARB_CNTL_DEFAULT[10]; ///< Arrays with values for CSR M3 arbiter for default.
  ULONG                       ulCSR_M3_ARB_CNTL_UVD[10];     ///< Arrays with values for CSR M3 arbiter for UVD playback.
  ULONG                       ulCSR_M3_ARB_CNTL_FS3D[10];    ///< Arrays with values for CSR M3 arbiter for Full Screen 3D applications.
  ATOM_AVAILABLE_SCLK_LIST    sAvail_SCLK[5];                ///< Arrays to provide availabe list of SLCK and corresponding voltage, order from low to high
  ULONG                       ulGMCRestoreResetTime;         ///< GMC power restore and GMC reset time to calculate data reconnection latency. Unit in ns.
  ULONG                       ulMinimumNClk;                 ///< Minimum NCLK speed among all NB-Pstates to calcualte data reconnection latency. Unit in 10kHz.
  ULONG                       ulIdleNClk;                    ///< NCLK speed while memory runs in self-refresh state. Unit in 10kHz.
  ULONG                       ulDDR_DLL_PowerUpTime;         ///< DDR PHY DLL power up time. Unit in ns.
  ULONG                       ulDDR_PLL_PowerUpTime;         ///< DDR PHY PLL power up time. Unit in ns
  USHORT                      usPCIEClkSSPercentage;         ///< usPCIEClkSSPercentage
  USHORT                      usPCIEClkSSType;               ///< usPCIEClkSSType
  USHORT                      usLvdsSSPercentage;            ///< usLvdsSSPercentage
  USHORT                      usLvdsSSpreadRateIn10Hz;       ///< usLvdsSSpreadRateIn10Hz
  USHORT                      usHDMISSPercentage;            ///< usHDMISSPercentage
  USHORT                      usHDMISSpreadRateIn10Hz;       ///< usHDMISSpreadRateIn10Hz
  USHORT                      usDVISSPercentage;             ///< usDVISSPercentage
  USHORT                      usDVISSpreadRateIn10Hz;        ///< usDVISSpreadRateIn10Hz
  ULONG                       SclkDpmBoostMargin;            ///< SclkDpmBoostMargin
  ULONG                       SclkDpmThrottleMargin;         ///< SclkDpmThrottleMargin
  USHORT                      SclkDpmTdpLimitPG;             ///< SclkDpmTdpLimitPG
  USHORT                      SclkDpmTdpLimitBoost;          ///< SclkDpmTdpLimitBoost
  ULONG                       ulBoostEngineCLock;            ///< ulBoostEngineCLock
  UCHAR                       ulBoostVid_2bit;               ///< ulBoostVid_2bit
  UCHAR                       EnableBoost;                   ///< EnableBoost
  USHORT                      GnbTdpLimit;                   ///< GnbTdpLimit
  USHORT                      usMaxLVDSPclkFreqInSingleLink; ///< usMaxLVDSPclkFreqInSingleLink
  UCHAR                       ucLvdsMisc;                    ///< ucLvdsMisc
  UCHAR                       ucLVDSReserved;                ///< ucLVDSReserved
  ULONG                       ulReserved3[15];               ///< Reserved
  ATOM_EXTERNAL_DISPLAY_CONNECTION_INFO sExtDispConnInfo;    ///< Display connector definition
} ATOM_INTEGRATED_SYSTEM_INFO_V6;

/// this Table is used for Llano/Ontario APU
typedef struct _ATOM_FUSION_SYSTEM_INFO_V1 {
  ATOM_INTEGRATED_SYSTEM_INFO_V6    sIntegratedSysInfo;      ///< Refer to ATOM_INTEGRATED_SYSTEM_INFO_V6 definition.
  ULONG                             ulPowerplayTable[128];   ///< This 512 bytes memory is used to save ATOM_PPLIB_POWERPLAYTABLE3, starting form ulPowerplayTable[0]
} ATOM_FUSION_SYSTEM_INFO_V1;

/// Integrated Info table
/// Upgrade is followed by Trinity SBIOS/VBIOS & Driver interface Design Document VER 0.5
typedef struct _ATOM_INTEGRATED_SYSTEM_INFO_V1_7 {
  ATOM_COMMON_TABLE_HEADER    sHeader;                       ///< Standard Header
  ULONG                       ulBootUpEngineClock;           ///< VBIOS bootup Engine clock frequency, in 10kHz unit.
  ULONG                       ulDentistVCOFreq;              ///< Dentist VCO clock in 10kHz unit.
  ULONG                       ulBootUpUMAClock;              ///< System memory boot up clock frequency in 10Khz unit.
  ATOM_CLK_VOLT_CAPABILITY    sDISPCLK_Voltage[4];           ///< Report Display clock voltage requirement.
  ULONG                       ulBootUpReqDisplayVector;      /**< VBIOS boot up display IDs, following are supported devices in Llano/Fam 12 and Ontario/Fam 14 projects:
                                                               * ATOM_DEVICE_CRT1_SUPPORT                  0x0001
                                                               * ATOM_DEVICE_CRT2_SUPPORT                  0x0010
                                                               * ATOM_DEVICE_DFP1_SUPPORT                  0x0008
                                                               * ATOM_DEVICE_DFP6_SUPPORT                  0x0040
                                                               * ATOM_DEVICE_DFP2_SUPPORT                  0x0080
                                                               * ATOM_DEVICE_DFP3_SUPPORT                  0x0200
                                                               * ATOM_DEVICE_DFP4_SUPPORT                  0x0400
                                                               * ATOM_DEVICE_DFP5_SUPPORT                  0x0800
                                                               * ATOM_DEVICE_LCD1_SUPPORT                  0x0002
                                                               */
  ULONG                       ulOtherDisplayMisc;            ///< Other display related flags, not defined yet.
  ULONG                       ulGPUCapInfo;                  /**> @li BIT[0] - TMDS/HDMI Coherent Mode 0: use cascade PLL mode, 1: use signel PLL mode.
                                                               *  @li BIT[1] - DP mode 0: use cascade PLL mode, 1: use single PLL mode
                                                               *  @li BIT[3] - AUX HW mode detection logic 0: Enable, 1: Disable
                                                               */
  ULONG                       ulSB_MMIO_Base_Addr;           ///< Physical Base address to SB MMIO space. Driver need to initialize it for SMU usage.
  USHORT                      usRequestedPWMFreqInHz;        ///< Panel Required PWM frequency. if this parameter is 0 PWM from to control LCD Backlight will be disabled.
  UCHAR                       ucHtcTmpLmt;                   ///< HTC temperature limit.The processor enters HTC-active state when Tctl reaches or exceeds HtcHystLmt.
  UCHAR                       ucHtcHystLmt;                  ///< HTC hysteresis.The processor exits HTC-active state when Tctl is less than HtcTmpLmt minus HtcHystLmt.
  ULONG                       ulMinEngineClock;              ///< Min SCLK
  ULONG                       ulSystemConfig;                ///< TBD
  ULONG                       ulCPUCapInfo;                  ///< TBD
  USHORT                      usNBP0Voltage;                 ///< VID for voltage on NB P0 State
  USHORT                      usNBP1Voltage;                 ///< VID for voltage on NB P1 State
  USHORT                      usBootUpNBVoltage;             ///< Voltage Index of GNB voltage configured by SBIOS, which is sufficient to support VBIOS DISPCLK requirement.
  USHORT                      usExtDispConnInfoOffset;       ///< Offset to sExtDispConnInfo inside the structure
  USHORT                      usPanelRefreshRateRange;       /**< Bit vector for LVDS/eDP supported refresh rate range. If DRR is enabled, 2 of the bits must be set.
                                                               * SUPPORTED_LCD_REFRESHRATE_30Hz          0x0004
                                                               * SUPPORTED_LCD_REFRESHRATE_40Hz          0x0008
                                                               * SUPPORTED_LCD_REFRESHRATE_50Hz          0x0010
                                                               * SUPPORTED_LCD_REFRESHRATE_60Hz          0x0020
                                                               */
  UCHAR                       ucMemoryType;                  ///< Memory type (3 for DDR3)
  UCHAR                       ucUMAChannelNumber;            ///< System memory channel numbers.
  UCHAR                       strVBIOSMsg[40];               ///< Allow customer to have its own VBIOS message
  ULONG                       ulReserved[20];                ///<
  ATOM_AVAILABLE_SCLK_LIST    sAvail_SCLK[5];                ///< Arrays to provide availabe list of SLCK and corresponding voltage, order from low to high
  ULONG                       ulGMCRestoreResetTime;         ///< GMC power restore and GMC reset time to calculate data reconnection latency. Unit in ns.
  ULONG                       ulMinimumNClk;                 ///< Minimum NCLK speed among all NB-Pstates to calcualte data reconnection latency. Unit in 10kHz.
  ULONG                       ulIdleNClk;                    ///< NCLK speed while memory runs in self-refresh state. Unit in 10kHz.
  ULONG                       ulDDR_DLL_PowerUpTime;         ///< DDR PHY DLL power up time. Unit in ns.
  ULONG                       ulDDR_PLL_PowerUpTime;         ///< DDR PHY PLL power up time. Unit in ns
  USHORT                      usPCIEClkSSPercentage;         ///<
  USHORT                      usPCIEClkSSType;               ///<
  USHORT                      usLvdsSSPercentage;            ///<
  USHORT                      usLvdsSSpreadRateIn10Hz;       ///<
  USHORT                      usHDMISSPercentage;            ///<
  USHORT                      usHDMISSpreadRateIn10Hz;       ///<
  USHORT                      usDVISSPercentage;             ///<
  USHORT                      usDVISSpreadRateIn10Hz;        ///<
  ULONG                       SclkDpmBoostMargin;            ///<
  ULONG                       SclkDpmThrottleMargin;         ///<
  USHORT                      SclkDpmTdpLimitPG;             ///<
  USHORT                      SclkDpmTdpLimitBoost;          ///<
  ULONG                       ulBoostEngineCLock;            ///<
  UCHAR                       ulBoostVid_2bit;               ///<
  UCHAR                       EnableBoost;                   ///<
  USHORT                      GnbTdpLimit;                   ///<
  USHORT                      usMaxLVDSPclkFreqInSingleLink; ///<
  UCHAR                       ucLvdsMisc;                    ///<
  UCHAR                       gnbgfxline429 ;        ///<
  UCHAR                       ucLVDSPwrOnSeqDIGONtoDE_in4Ms; ///<
  UCHAR                       ucLVDSPwrOnSeqDEtoVARY_BL_in4Ms;    ///<
  UCHAR                       ucLVDSPwrOffSeqVARY_BLtoDE_in4Ms;   ///<
  UCHAR                       ucLVDSPwrOffSeqDEtoDIGON_in4Ms;     ///<
  UCHAR                       ucLVDSOffToOnDelay_in4Ms;           ///<
  UCHAR                       ucLVDSPwrOnSeqVARY_BLtoBLON_in4Ms;  ///<
  UCHAR                       ucLVDSPwrOffSeqBLONtoVARY_BL_in4Ms; ///<
  UCHAR                       ucLVDSReserved1;                    ///<
  ULONG                       ulLCDBitDepthControlVal;            ///<
  ULONG                       ulNbpStateMemclkFreq[4];            ///<
  USHORT                      usNBP2Voltage;                      ///<
  USHORT                      usNBP3Voltage;                      ///<
  ULONG                       ulNbpStateNClkFreq[4];              ///<
  UCHAR                       ucNBDPMEnable;                      ///<
  UCHAR                       ucReserved[3];                      ///<
  UCHAR                       ucDPMState0VclkFid;                 ///<
  UCHAR                       ucDPMState0DclkFid;                 ///<
  UCHAR                       ucDPMState1VclkFid;                 ///<
  UCHAR                       ucDPMState1DclkFid;                 ///<
  UCHAR                       ucDPMState2VclkFid;                 ///<
  UCHAR                       ucDPMState2DclkFid;                 ///<
  UCHAR                       ucDPMState3VclkFid;                 ///<
  UCHAR                       ucDPMState3DclkFid;                 ///<
  ATOM_EXTERNAL_DISPLAY_CONNECTION_INFO sExtDispConnInfo;         ///<
} ATOM_INTEGRATED_SYSTEM_INFO_V1_7;

/// this Table is used for Llano/Ontario APU
typedef struct _ATOM_FUSION_SYSTEM_INFO_V2 {
  ATOM_INTEGRATED_SYSTEM_INFO_V1_7  sIntegratedSysInfo;      ///< Refer to ATOM_INTEGRATED_SYSTEM_INFO_V1_7 definition.
  ULONG                             ulPowerplayTable[128];   ///< This 512 bytes memory is used to save ATOM_PPLIB_POWERPLAYTABLE3, starting form ulPowerplayTable[0]
} ATOM_FUSION_SYSTEM_INFO_V2;

#define GNB_SBDFO MAKE_SBDFO(0, 0, 0, 0, 0)

/// Define configuration values for ulGPUCapInfo
// BIT[0] - TMDS/HDMI Coherent Mode 0: use cascade PLL mode, 1: use signel PLL mode.
#define GPUCAPINFO_TMDS_HDMI_USE_CASCADE_PLL_MODE      0x00ul
#define GPUCAPINFO_TMDS_HDMI_USE_SINGLE_PLL_MODE       0x01ul

// BIT[1] - DP mode 0: use cascade PLL mode, 1: use single PLL mode
#define GPUCAPINFO_DP_MODE_USE_CASCADE_PLL_MODE        0x00ul
#define GPUCAPINFO_DP_USE_SINGLE_PLL_MODE              0x02ul

// BIT[3] - AUX HW mode detection logic 0: Enable, 1: Disable
#define GPUCAPINFO_AUX_HW_MODE_DETECTION_ENABLE        0x00ul
#define GPUCAPINFO_AUX_HW_MODE_DETECTION_DISABLE       0x08ul

#endif
