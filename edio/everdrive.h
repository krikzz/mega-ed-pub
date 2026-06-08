/* 
 * File:   everdrive.h
 * Author: igor
 *
 * Created on January 23, 2020, 6:31 PM
 */

#include "sys.h"

#ifndef EVERDRIVE_H
#define	EVERDRIVE_H

/*----------------------------------------------------------------
 * cpu memory map:
 * 0x000000 256K OS code
 * 0x040000 256K OS ram
 * 0x080000 256K Save state buffer
 * 0xA130D0 16B control registers
 * ---------------------------------------------------------------- SST structure
 * 0x00000 64K  cpu ram
 * 0x10000 64K  vdp ram
 * 0x20000 128B sniffer
 * 0x20080 128B mapper regs
 * 0x20100 64B  cpu regs
 * 0x20140 128B vdp pal
 * 0x201C0 80B  vdp scroll
 * 0x20210 2B   halt st
 * 0x20212 ??   unused
 * 0x24000 64K  bram
 */

#define DEVID_MEGAPRO           0x18
#define DEVID_MEGACORE          0x25

#define STATUS_KEY_OLD          0xA5
#define STATUS_KEY              0x5A
#define PROTOCOL_ID             0x05

#define ERR_UNXP_STAT           0x40
#define ERR_NULL_PATH           0x41
//****************************************************************************** mappers

typedef enum {
    MAP_OS = 0,
    MAP_SMD, //1
    MAP_32X, //2
    MAP_10M, //3
    MAP_CDB, //4

    MAP_SSF, //5
    MAP_SMS, //6
    MAP_SVP, //7
    MAP_MCD, //8
    MAP_PIE, //9
    MAP_PIE_CD, //10
    MAP_SMD_CD, //11
    MAP_NES, //12
    MAP_GKO, //13
    MAP_END
} MAP_DEF;


//****************************************************************************** edio
typedef struct {
    vu8 reserved0;
    vu8 FIFODATA; //    R/W  Fifo data register
    vu16 FIFOSTAT; //   R    Fifo status register. shows if fifo can be readed.
    vu16 SYSSTAT; //    R    Last cmd status
    vu16 TIMER; //      R    System timer, 16bit, 1ms resolution
    vu8 reserved1;
    vu8 MEMDATA;//      R/W  Mem data
    vu8 reserved2;
    vu8 MEMADDR;//      W    Mem addr (serial). required using MEM_WP_MASK
    vu16 SSTCTRL;//     W    IGM handler controls
    vu16 MBX;//         R/W  gp mailbox register (mirror at ADDR_FCI_MBX)
} Edio;

#define EDIO_BASE       0xA130D0
#define EDIO            ((Edio *) EDIO_BASE)

#define FIFO_CPU_RXF    0x8000 //fifo flags. system cpu can read
#define FIFO_ARM_RXF    0x4000 //fifo flags. mcu can read
#define FIFO_RXF_MSK    0x7FF

#define STATUS_CFG_OK   0x01 //mcu completed system configuration and. System ready for cpu execution
#define STATUS_CMD_OK   0x02 //mcu finished command execution
#define STATUS_FPG_OK   0x04 //fpga reboot complete
#define STATUS_STROBE   0x08 //toggled after each read
#define STATUS_REBOOT   0x10 //isn't real status. just an request to reboot at the end of halt

#define HOST_RST_SOFT   0x01
#define HOST_RST_HARD   0x02

#define MEM_WP_MASK     0x80000000
//******************************************************************************
//FCI bus addresses space
#define ADDR_FCI_ROM    0x00000000 //ROM MEMORY    (2x8MB PSRAM)
#define ADDR_FCI_DBUF   0x00F00000 //data buffer 256K. sms sst use it as SST_BUFF
#define ADDR_FCI_SST_BF 0x00F40000 //current save state 256K
#define ADDR_FCI_MENU   0x00F80000 //menu program
#define ADDR_FCI_SST_MS 0x00EF0000 //sms sst core. mapped to the end of menu ram
#define ADDR_FCI_SRAM   0x01000000 //SRAM          (fast 10ns mem)
#define ADDR_FCI_BRAM   0x01080000 //Batery RAM 
#define ADDR_FCI_CFG    0x01800000 //various system configs
#define ADDR_FCI_SST_SR 0x01800100 //save state. sniffer data and mapper registers if any. !used by sms core!
#define ADDR_FCI_MSTAT  0x01800200 //mapper status
#define ADDR_FCI_MBX    0x01800300 //gp mailbox
#define ADDR_FCI_FIFO   0x01810000 //fifo buffer
#define ADDR_FCI_MAP    0x01830000 //mapper registers
#define ADDR_FCI_MCD    0x01840000 //mcd
#define ADDR_FCI_MDP    0x01850000 //MD+

#define ADDR_FCI_BRM_MD (ADDR_FCI_BRAM + 0x00000)//regular saves
#define ADDR_FCI_BRM_RC (ADDR_FCI_BRAM + 0x00000)//cd cart
#define ADDR_FCI_BRM_CD (ADDR_FCI_BRAM + 0x40000)//cd int bram

#define ADDR_FCI_MSBIOS (ADDR_FCI_ROM  + 0x400000)
#define ADDR_FCI_CDBIOS (ADDR_FCI_BRAM + 0x60000)

#define ADDR_FCI_MAPCFG (ADDR_FCI_MAP  + 0xFF00)  //mapper specific config
#define ADDR_FCI_MCDCFG (ADDR_FCI_MCD  + 0xFF00)  //mapper specific config
#define ADDR_FCI_MARKS  (ADDR_FCI_MENU + 0x00180)
#define ADDR_FCI_CFGCC  (ADDR_FCI_CFG + 0)        //rom cheats config
#define ADDR_FCI_CFGMAP (ADDR_FCI_CFG + 128)      //mapper config


#define ADDR_FLA_MENU   0x00000         //boot fails cpu code
#define ADDR_FLA_FPGA   0x40000         //boot fails fpga code
#define ADDR_FLA_ICOR   0x80000         //mcu firmware update

#define SIZE_MENU_CODE  0x40000         //MENU CODE SIZE 
#define SIZE_MENU_WRAM  0x30000         //MENU RAM SIZE (last 64k used for sms sst core)
#define SIZE_FIFO       2048            //fifo buffer size between cpu and mcu
#define SIZE_DBUF       0x40000         //IO buffer size. actually 256K


#define GG_SLOTS        16
#define SS_COMBO_OFF    0xFFF   //turn off ss combo val
#define MAP_MOD_NSP     0xA5    //mapper not supported
#define MAP_MOD_MCD     0x01    //mcd mode
#define MAP_MOD_MDP     0x02    //md+ mode
//****************************************************************************** file mode
#define	FA_READ			0x01
#define	FA_WRITE		0x02
#define	FA_OPEN_EXISTING	0x00
#define	FA_CREATE_NEW		0x04
#define	FA_CREATE_ALWAYS	0x08
#define	FA_OPEN_ALWAYS		0x10
#define	FA_OPEN_APPEND		0x30

#define	AT_RDO                  0x01	/* Read only */
#define	AT_HID                  0x02	/* Hidden */
#define	AT_SYS                  0x04	/* System */
#define AT_DIR                  0x10	/* Directory */
#define AT_ARC                  0x20	/* Archive */

#define DIR_OPT_SORTED          0x01
#define DIR_OPT_HIDESYS         0x02
#define DIR_OPT_SEEKCUE         0x04
#define DIR_OPT_FILTCUE         0x08
#define DIR_OPT_FILTROM         0x10
#define DIR_OPT_FILTRBF         0x20
#define DIR_OPT_CUTFNAM         0x80
//****************************************************************************** system control
#define SYS_CTRL_RSTOFF         0x01    //with this option quick reset wil reset the game but will not return to menu
#define SYS_CTRL_SST_ON         0x02    //vblank hook for in-game menu
#define SYS_CTRL_GG_ON          0x04    //cheats engine
#define SYS_CTRL_SST_BTN        0x08    //use external button for save state
#define SYS_CTRL_MEGASG         0x10    //hacks for eliminating mega-sg bugs
#define SYS_CTRL_32X            0x20    //specific reset mode for 32x
#define SYS_CTRL_SMS            0x40    //specific reset and sst mode for sms
#define SYS_CTRL_GMODE          0x80    //mcu sets this bit when fpga configuration complete.
//****************************************************************************** features
#define FEA_MCD         0x01    //eable mcd core
#define FEA_MDP         0x02    //eable MD+
#define FEA_EXT         0x04    //extension unit simulation
//****************************************************************************** game mapper control
#define BRAM_OFF        0x00
#define BRAM_SRM        0x01
#define BRAM_SRM3M      0x02
#define BRAM_24X01      0x03
#define BRAM_24C01      0x04
#define BRAM_24C02      0x05
#define BRAM_24C08      0x06
#define BRAM_24C16      0x07
#define BRAM_24C64      0x08
#define BRAM_M95320     0x09
#define BRAM_RCART      0x0A

#define BRAM_BUS_ACLM   0x00 //D=200001(0), C=200000(0)
#define BRAM_BUS_EART   0x10 //D=200000(7), C=200000(6)
#define BRAM_BUS_SEGA   0x20 //D=200001(0), C=200001(1)
#define BRAM_BUS_CODM   0x30 //D=300000(0), C=300000(1), RD=380001(7)

#define BRAM_MSK_TYPE   0x0F
#define BRAM_MSK_EBUS   0xF0

#define MCFG_MS_BIOS    0x01
#define MCFG_MS_FM      0x02
#define MCFG_MS_EXT     0x04
//****************************************************************************** 

typedef struct {
    u32 size;
    u16 date;
    u16 time;
    u8 is_dir;
    u8 *file_name;
} FileInfo;

typedef struct {
    u32 addr;
    u16 val;
    u16 unused;
} CheatSlot;

typedef struct {
    CheatSlot slot[GG_SLOTS];
} CheatList;

typedef struct {//lo/hi pass filter config
    u8 alpha; //filter alpha
    u8 gbase; //gain vol base
    u8 gfilt; //gain vol filt
    u8 gtotl; //gain total
} DspCfg;

typedef struct {
    CheatList gg;
    DspCfg lpf;
    DspCfg hpf;
    u16 mcd_irq_phase;
    u8 reserved[110];
    u8 map_idx;
    u8 mask;
    u8 map_cfg;
    u8 bram_cfg;
    u8 ss_key_save;
    u8 ss_key_load;
    u8 ss_key_menu;
    u8 sys_ctrl;
} MapConfig;

typedef struct {
    u16 v50;
    u16 v25;
    u16 v12;
    u16 vbt;
} Vdc;

typedef struct {
    u8 yar;
    u8 mon;
    u8 dom;
    u8 hur;
    u8 min;
    u8 sec;
} RtcTime;

typedef struct {
    u8 fla_id[8];
    u8 cpu_id[12];
    u32 serial_g;
    u32 serial_l;
    u32 boot_ctr;
    u32 game_ctr;
    u16 asm_date;
    u16 asm_time;
    u16 sw_date;
    u16 sw_time;
    u16 sw_ver;
    u16 hv_ver;
    u16 boot_ver;
    u8 device_id;
    u8 manufac_id;
    u8 rst_src;
    u8 boot_status;
    u8 bat_dry;
    u8 disk_status;
    u8 pwr_sys;
    u8 pwr_usb;
    u8 eep_id[6];
} SysInfoIO;

typedef struct {
    u16 vdp_regs[32];
    u8 reserved[63];
    u8 joy_keys;
    u8 map_regs[128];
} MapSSR_SMD;

typedef struct {
    u8 cpu_ram[0x10000];
    u8 vdp_ram[0x10000];
    MapSSR_SMD map_ssr;
    u32 cpu_reg[16];
    u16 vdp_crm[64];
    u16 vdp_vsr[40];
    u16 halt_st;
    u16 moto_sr;
    u8 unused[0x3DEC];
    u8 cpu_brm[0x10000];
} SaveState;



u8 ed_init();
void ed_cmd_status(u16 *status);
void ed_cmd_status2(void *status);
u8 ed_check_status();

//disk operations
u8 ed_cmd_disk_init();
u8 ed_cmd_dir_load(u8 *path, u8 args);
void ed_cmd_dir_get_size(u16 *size);
void ed_cmd_dir_seek_idx(u16 *idx);
void ed_cmd_dir_get_recs(u16 start_idx, u16 amount, u16 max_name_len);
u8 ed_cmd_file_open(u8 *path, u8 mode);
u8 ed_cmd_file_close();
u8 ed_cmd_file_read_mem(u32 addr, u32 len); //read to cartridge ram
u8 ed_cmd_file_read(void *dst, u32 len); //reat to system ram
u8 ed_cmd_file_write(void *src, u32 len); //write from system ram
u8 ed_cmd_file_write_mem(u32 addr, u32 len); //write from cartrifgr ram
u8 ed_cmd_file_info(u8 *path, FileInfo *inf);
u8 ed_cmd_file_set_ptr(u32 addr);
u8 ed_file_get_size(u8 *path, u32 *size);
u8 ed_cmd_file_del(u8 *path);


void ed_cmd_uart_wr(void *data, u16 len);
void ed_cmd_usb_wr(void *data, u16 len);
void ed_cmd_fifo_wr(void *data, u16 len);
u8 ed_cmd_file_crc(u32 len, u32 *crc_base);
void ed_cmd_mem_set(u8 val, u32 addr, u32 len);
u8 ed_cmd_mem_test(u8 val, u32 addr, u32 len);
void ed_cmd_mem_rd(u32 addr, void *dst, u32 len);
void ed_cmd_mem_wr(u32 addr, void *src, u32 len);
void ed_cmd_mem_crc(u32 addr, u32 len, u32 *crc_base);
void ed_cmd_upd_exec(u32 addr, u32 crc);
void ed_cmd_get_vdc(Vdc *vdc);
void ed_cmd_rtc_get(RtcTime *time);
void ed_cmd_rtc_set(RtcTime *time);
void ed_cmd_sys_inf(SysInfoIO *inf);
void ed_cmd_reboot();
void ed_cmd_game_ctr();
void ed_cmd_fla_rd(void *dst, u32 addr, u32 len);
u8 ed_cmd_fla_wr_sdc(u32 addr, u32 len);
u8 ed_cmd_fpga_init(u8 *path);
u8 ed_cmd_rom_path(u8 *path, u8 path_type);

void ed_tx_string(u8 *string);
void ed_rx_string(u8 *string);
u8 ed_rx_next_rec(FileInfo *inf);
void ed_fifo_wr(void *data, u16 len);
void ed_fifo_rd(void *data, u16 len);
u8 ed_fifo_busy();

void ed_sleep(u16 ms);
u16 ed_get_ticks();


#endif	/* EVERDRIVE_H */

