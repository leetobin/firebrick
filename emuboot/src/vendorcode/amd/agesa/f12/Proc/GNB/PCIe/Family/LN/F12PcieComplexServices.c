/* $NoKeywords:$ */
/**
 * @file
 *
 * Family specific PCIe complex initialization services
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 49532 $   @e \$Date: 2011-03-25 02:54:43 +0800 (Fri, 25 Mar 2011) $
 *
 */
/*
*****************************************************************************
*
* Copyright (c) 2011, Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Advanced Micro Devices, Inc. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ADVANCED MICRO DEVICES, INC. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* ***************************************************************************
*
*/
/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include  "AGESA.h"
#include  "Ids.h"
#include  "Gnb.h"
#include  "GnbPcie.h"
#include  "GnbCommonLib.h"
#include  "GnbPcieInitLibV1.h"
#include  "GnbPcieConfig.h"
#include  "PcieFamilyServices.h"
#include  "GnbPcieFamServices.h"
#include  "LlanoDefinitions.h"
#include  "GnbRegistersLN.h"
#include  "NbSmuLib.h"
#include  "Filecode.h"
#include  "GnbPcieInitLibV1.h"
#define FILECODE PROC_GNB_PCIE_FAMILY_LN_F12PCIECOMPLEXSERVICES_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------*/
/**
 * Control port visability
 *
 *
 * @param[in]  Control             Hide/Unhide control
 * @param[in]  Silicon             Pointer to silicon configuration descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 */

VOID
PcieFmPortVisabilityControl (
  IN      PCIE_PORT_VISIBILITY  Control,
  IN      PCIe_SILICON_CONFIG   *Silicon,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  switch (Control) {
  case UnhidePorts:
    PcieSiliconUnHidePorts (Silicon, Pcie);
    break;
  case HidePorts:
    PcieSiliconHidePorts (Silicon, Pcie);
    break;
  default:
    ASSERT (FALSE);
  }
}


/*----------------------------------------------------------------------------------------*/
/**
 * Request boot up voltage
 *
 *
 *
 * @param[in]  LinkCap             Global GEN capability
 * @param[in]  Pcie                Pointer to PCIe configuration data area
 */
VOID
PcieFmSetBootUpVoltage (
  IN      PCIE_LINK_SPEED_CAP   LinkCap,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  FCRxFE00_4036_STRUCT  FCRxFE00_4036;
  D18F3x15C_STRUCT      D18F3x15C;
  UINT8                 TargetVidIndex;
  UINT32                Temp;
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieFmSetBootUpVoltage Enter\n");
  GnbLibPciRead (
    MAKE_SBDFO ( 0, 0, 0x18, 3, D18F3x15C_ADDRESS),
    AccessWidth32,
    &D18F3x15C.Value,
    GnbLibGetHeader (Pcie)
    );
  Temp = D18F3x15C.Value;
  if (LinkCap > PcieGen1) {
    FCRxFE00_4036.Value = NbSmuReadEfuse (FCRxFE00_4036_ADDRESS, GnbLibGetHeader (Pcie));
    TargetVidIndex = (UINT8) FCRxFE00_4036.Field.PcieGen2Vid;
  } else {
    TargetVidIndex = PcieSiliconGetGen1VoltageIndex (GnbLibGetHeader (Pcie));
  }
  IDS_HDT_CONSOLE (PCIE_MISC, "  Set Voltage for Gen %d, Vid Index %d\n", LinkCap, TargetVidIndex);
  if (TargetVidIndex == 3) {
    D18F3x15C.Field.SclkVidLevel2 = D18F3x15C.Field.SclkVidLevel3;
    GnbLibPciWrite (
      MAKE_SBDFO ( 0, 0, 0x18, 3, D18F3x15C_ADDRESS),
      AccessWidth32,
      &D18F3x15C.Value,
      GnbLibGetHeader (Pcie)
      );
    PcieSiliconRequestVoltage (2, GnbLibGetHeader (Pcie));
  }
  GnbLibPciWrite (
    MAKE_SBDFO ( 0, 0, 0x18, 3, D18F3x15C_ADDRESS),
    AccessWidth32,
    &Temp,
    GnbLibGetHeader (Pcie)
    );
  PcieSiliconRequestVoltage (TargetVidIndex, GnbLibGetHeader (Pcie));
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieFmSetBootUpVoltage Exit\n");
}

/*----------------------------------------------------------------------------------------*/
/**
 * Map engine to specific PCI device address
 *
 *
 *
 * @param[in]  Engine              Pointer to engine configuration
 * @retval     AGESA_ERROR         Fail to map PCI device address
 * @retval     AGESA_SUCCESS       Successfully allocate PCI address
 */

AGESA_STATUS
PcieFmMapPortPciAddress (
  IN      PCIe_ENGINE_CONFIG     *Engine
  )
{
  PCIe_WRAPPER_CONFIG   *Wrapper;
  PCIe_PLATFORM_CONFIG  *Pcie;
  UINT64                ConfigurationSignature;

  Wrapper = PcieConfigGetParentWrapper (Engine);
  Pcie = (PCIe_PLATFORM_CONFIG *) PcieConfigGetParent (DESCRIPTOR_PLATFORM, &Engine->Header);
  if (Wrapper->WrapId == GPP_WRAP_ID) {
    ConfigurationSignature = PcieConfigGetConfigurationSignature (Wrapper, Engine->Type.Port.CoreId);
    if ((ConfigurationSignature == GPP_CORE_x4x2x1x1_ST) || (ConfigurationSignature == GPP_CORE_x4x2x2_ST)) {
      //Enable device remapping
      GnbLibPciIndirectRMW (
        MAKE_SBDFO (0, 0, 0, 0, D0F0x60_ADDRESS),
        D0F0x64_x20_ADDRESS | IOC_WRITE_ENABLE,
        AccessS3SaveWidth32,
        ~(UINT32) (1 << D0F0x64_x20_IocPcieDevRemapDis_OFFSET),
        0x0,
        GnbLibGetHeader (Pcie)
        );
    }
  }
  if (Engine->Type.Port.PortData.DeviceNumber == 0 && Engine->Type.Port.PortData.FunctionNumber == 0) {
    Engine->Type.Port.PortData.DeviceNumber = Engine->Type.Port.NativeDevNumber;
    Engine->Type.Port.PortData.FunctionNumber = Engine->Type.Port.NativeFunNumber;
    return AGESA_SUCCESS;
  }
  if (Engine->Type.Port.PortData.DeviceNumber ==  Engine->Type.Port.NativeDevNumber &&
    Engine->Type.Port.PortData.FunctionNumber ==  Engine->Type.Port.NativeFunNumber) {
    return AGESA_SUCCESS;
  }
  return  AGESA_ERROR;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Set slo power limit
 *
 *
 *
 * @param[in]  Engine              Pointer to engine configuration
 * @param[in]  Pcie                Pointer to PCIe configuration
 */


VOID
PcieFmEnableSlotPowerLimit (
  IN      PCIe_ENGINE_CONFIG     *Engine,
  IN      PCIe_PLATFORM_CONFIG   *Pcie
  )
{
  ASSERT (Engine->EngineData.EngineType == PciePortEngine);
  if (PcieLibIsEngineAllocated (Engine) && Engine->Type.Port.PortData.PortPresent != PortDisabled && !PcieConfigIsSbPcieEngine (Engine)) {
    IDS_HDT_CONSOLE (PCIE_MISC, "   Enable Slot Power Limit for Port % d\n", Engine->Type.Port.Address.Address.Device);
    GnbLibPciIndirectRMW (
      MAKE_SBDFO (0, 0, 0, 0, D0F0x60_ADDRESS),
      (D0F0x64_x51_ADDRESS + (Engine->Type.Port.Address.Address.Device - 2) * 2) | IOC_WRITE_ENABLE,
      AccessS3SaveWidth32,
      0xffffffff,
      1 << D0F0x64_x51_SetPowEn_OFFSET,
      GnbLibGetHeader (Pcie)
    );
  }
}

