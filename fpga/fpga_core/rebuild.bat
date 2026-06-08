set PATH=C:\intelFPGA_lite\20.1\quartus\bin64\


start quartus_sh --flow compile  map_smd/mega-core
start quartus_sh --flow compile  map_smd_cd/mega-core
start quartus_sh --flow compile  map_ssf/mega-core
start quartus_sh --flow compile  map_svp/mega-core


