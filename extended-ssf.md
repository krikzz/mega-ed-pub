# Extended-SSF Mapper

The Extended-SSF mapper provides eight configurable 512 KiB cartridge memory windows and supports up to **32 banks of 512 KiB**, for a total addressable memory capacity of **16 MiB**. Bank indices range from `0` to `31`.

**Backup RAM is mapped to bank 31**, the last bank.

To activate the Extended-SSF mapper, replace the standard "SEGA MEGA DRIVE" string in the ROM header at offset `0x100` with "SEGA SSF".

## Cartridge Memory Map

The cartridge address space contains eight 512 KiB windows. Each window maps to the memory bank selected by its corresponding control register.

| Address range | Window | Control register |
| --- | --- | --- |
| `0x000000–0x07FFFF` | `WIN0` | `CTRL0` |
| `0x080000–0x0FFFFF` | `WIN1` | `CTRL1` |
| `0x100000–0x17FFFF` | `WIN2` | `CTRL2` |
| `0x180000–0x1FFFFF` | `WIN3` | `CTRL3` |
| `0x200000–0x27FFFF` | `WIN4` | `CTRL4` |
| `0x280000–0x2FFFFF` | `WIN5` | `CTRL5` |
| `0x300000–0x37FFFF` | `WIN6` | `CTRL6` |
| `0x380000–0x3FFFFF` | `WIN7` | `CTRL7` |

## Control Registers

| Address | Register | Bit layout (15–0) |
| --- | --- | --- |
| `0xA130F0` | `CTRL0` | `P.WLC... ...RRRRR` |
| `0xA130F2` | `CTRL1` | `........ ...RRRRR` |
| `0xA130F4` | `CTRL2` | `........ ...RRRRR` |
| `0xA130F6` | `CTRL3` | `........ ...RRRRR` |
| `0xA130F8` | `CTRL4` | `........ ...RRRRR` |
| `0xA130FA` | `CTRL5` | `........ ...RRRRR` |
| `0xA130FC` | `CTRL6` | `........ ...RRRRR` |
| `0xA130FE` | `CTRL7` | `........ ...RRRRR` |

Each `CTRLx` register selects the 512 KiB memory bank mapped to the corresponding `WINx` window. `CTRL0` also provides additional control functions.

All control registers are **write-only** and accept **16-bit writes only**.

### CTRL0 Bit Fields

| Bit(s) | Field | Description |
| --- | --- | --- |
| 15 | `P` | Protection bit. Must be set to `1` when writing to `CTRL0` (`0xA130F0`). |
| 13 | `W` | Memory write protection: `0` = protected, `1` = writable. |
| 12 | `L` | LED control: `0` = off, `1` = on. |
| 11 | `C` | `#CART` signal control. Directly controls the `#CART` line. Setting this bit swaps the cartridge (`0x000000–0x3FFFFF`) and Sega-CD (`0x400000–0x7FFFFF`) address spaces. |
| 4–0 | `R` | Memory bank selection (`0–31`); each bank is 512 KiB. |

The `P`, `W`, `L`, and `C` fields are available only in `CTRL0`. The `R` field is available in all eight control registers. Dots (`.`) in the bit layouts indicate fields not defined in this specification.
