# EDAPP Examples

Starting from firmware version `4.08`, the system supports association of specific file types with external applications.

This feature is mainly designed for external emulators, but can also be used for other purposes such as the built-in MegaColor player.

If a file extension matches one of the folder names inside `MEGA/edapp`, the file will be executed using `app.md` stored in that folder.

## Execution Flow

- `app.md` is loaded at the beginning of the ROM memory space
- the target file is loaded right after `app.md`
- depending on `config.txt`, the system may pass:
  - target file binary data
  - or only path to the target file
- `app.md` may use a custom mapper if `mapper.rbf` is stored in the same folder

Refer to `MEGA/edapp` folders for implementation examples.

## config.txt

### inc modes

| Value | Description |
|---|---|
| `0` | Include target file binary data. |
| `1` | Include path to the target file. |

Included data is placed in ROM memory right after the end of `app.md`.

### exec modes

| Value | Description |
|---|---|
| `1` | Include application in recently played list. |
| `2` | Do not include application in recently played list. |

### bram size

Backup memory size is calculated as:

```text
size = 8192 << (val - 1)
