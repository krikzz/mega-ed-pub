# FPGA Mapper Examples

## Contents

| Path | Description |
|---|---|
| `/fpga_core` | Project files for Mega EverDrive CORE. |
| `/fpga_pro` | Project files for Mega EverDrive PRO. |
| `/mapper` | Shared mapper sources: system layers, mapper cores, helper modules, etc. |

## Shared Libraries

| Path | Description |
|---|---|
| `/mapper/lib_base` | System layer implementation. |
| `/mapper/lib_bram` | Backup memory implementation. |
| `/mapper/lib_mcd` | Mega-CD core. |

## Mapper Examples

| Path | Description |
|---|---|
| `/map_mcd` | Mega-CD mapper. |
| `/map_smd` | Regular Genesis mapper. |
| `/map_smd_cd` | Regular Genesis mapper with Mega-CD core and MD+ support. |
| `/map_ssf` | Super Street Fighter mapper with MD+ support. |
| `/map_svp` | SVP mapper used by Virtua Racing. |
| `/SE` | Simplified mapper without system layer. Can be used as a simple base for custom mappers. |

## Mapper Installation

For Mega EverDrive PRO:
- put `mega-pro.rbf` in the same folder as the ROM

For Mega EverDrive CORE:
- rename `mega-core.rbf` to `mega-core.x25`
- put it in the same folder as the ROM

Mappers can also be loaded via USB for testing.