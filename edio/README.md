# EDIO Sample

This sample shows how to use Mega EverDrive I/O features.

## Features

- Disk access
- USB communication
- Getting the path to the currently loaded ROM
- Access to ROM memory
- Read RTC
- Read Devie ID
- Base cartridge hardware library implementation in `everdrive.c`

## Scripts

| Path | Description |
|---|---|
| `usbrun.py` | Loads and runs `edio.md` via USB. |
| `../edio-cmd/usb_txt_rx.py` | Receives a text string from the console via USB. |
| `../edio-cmd/usb_txt_tx.py` | Sends text from `message.txt` via USB for printing on screen. |