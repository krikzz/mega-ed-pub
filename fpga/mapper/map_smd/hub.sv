

`include "../lib_base/defs.sv"


module map_hub(

	input  MapIn mai,
	output MapOut mao
);
	
	
	assign mao = 
	mai.cfg.map_idx == `MAP_SMD  ? mout_smd : 
	mai.cfg.map_idx == `MAP_CDB  ? mout_cdb :
	mai.cfg.map_idx == `MAP_10M  ? mout_smd :
										    mout_nom;
	
	
	MapOut mout_nom;
	map_nom nom_inst(mai, mout_nom);
	
	MapOut mout_smd;
	map_smd smd_inst(mai, mout_smd);
	
	MapOut mout_cdb;
	map_cdb cdb_inst(mai, mout_cdb);
	

	
endmodule
