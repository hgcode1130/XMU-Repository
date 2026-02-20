//----------------------------------------------系统时钟------------------------------------
set_property -dict {PACKAGE_PIN W19 IOSTANDARD LVCMOS33} [get_ports sys_clk_50m]
set_property -dict {PACKAGE_PIN H4    IOSTANDARD LVCMOS33} [get_ports sys_clk_100m]
set_property -dict {PACKAGE_PIN Y18   IOSTANDARD LVCMOS33} [get_ports sys_clk_3hz]


//---------------------------------------------LED0~LED7（DAC_D0~DAC_D7�?------------------
set_property -dict {PACKAGE_PIN AA21 IOSTANDARD LVCMOS33} [get_ports {led_pin[0]}]
set_property -dict {PACKAGE_PIN AA20 IOSTANDARD LVCMOS33} [get_ports {led_pin[1]}]
set_property -dict {PACKAGE_PIN W22  IOSTANDARD LVCMOS33} [get_ports {led_pin[2]}]
set_property -dict {PACKAGE_PIN W21  IOSTANDARD LVCMOS33} [get_ports {led_pin[3]}]
set_property -dict {PACKAGE_PIN T20   IOSTANDARD LVCMOS33} [get_ports {led_pin[4]}]
set_property -dict {PACKAGE_PIN R19   IOSTANDARD LVCMOS33} [get_ports {led_pin[5]}]
set_property -dict {PACKAGE_PIN P19   IOSTANDARD LVCMOS33} [get_ports {led_pin[6]}]
set_property -dict {PACKAGE_PIN U21   IOSTANDARD LVCMOS33} [get_ports {led_pin[7]}]



//---------------------------------------------拨码�?关sw0~sw7----------------------------------
set_property -dict {PACKAGE_PIN AA19 IOSTANDARD LVCMOS33} [get_ports {sw_pin[0]}]
set_property -dict {PACKAGE_PIN V19   IOSTANDARD LVCMOS33} [get_ports {sw_pin[1]}]
set_property -dict {PACKAGE_PIN V18   IOSTANDARD LVCMOS33} [get_ports {sw_pin[2]}]
set_property -dict {PACKAGE_PIN Y19   IOSTANDARD LVCMOS33} [get_ports {sw_pin[3]}]
set_property -dict {PACKAGE_PIN V20   IOSTANDARD LVCMOS33} [get_ports {sw_pin[4]}]
set_property -dict {PACKAGE_PIN U20   IOSTANDARD LVCMOS33} [get_ports {sw_pin[5]}]
set_property -dict {PACKAGE_PIN AB22 IOSTANDARD LVCMOS33} [get_ports {sw_pin[6]}]
set_property -dict {PACKAGE_PIN AB21 IOSTANDARD LVCMOS33} [get_ports {sw_pin[7]}]



//-----------------------------------------------9个按�?--------------------------------------
set_property -dict {PACKAGE_PIN F4     IOSTANDARD LVCMOS33} [get_ports btn_0]
set_property -dict {PACKAGE_PIN C2     IOSTANDARD LVCMOS33} [get_ports btn_1]
set_property -dict {PACKAGE_PIN B2     IOSTANDARD LVCMOS33} [get_ports btn_2]
set_property -dict {PACKAGE_PIN E2     IOSTANDARD LVCMOS33} [get_ports btn_3]
set_property -dict {PACKAGE_PIN D2    IOSTANDARD LVCMOS33} [get_ports btn_4]
set_property -dict {PACKAGE_PIN U22  IOSTANDARD LVCMOS33} [get_ports btn_5]
set_property -dict {PACKAGE_PIN V22  IOSTANDARD LVCMOS33} [get_ports btn_6]
set_property -dict {PACKAGE_PIN T21  IOSTANDARD LVCMOS33} [get_ports btn_7]
set_property -dict {PACKAGE_PIN W20 IOSTANDARD LVCMOS33} [get_ports btn_8]


set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets btn_0_IBUF]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets btn_1_IBUF]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets btn_2_IBUF]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets btn_3_IBUF]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets btn_4_IBUF]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets btn_5_IBUF]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets btn_6_IBUF]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets btn_7_IBUF]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets btn_8_IBUF]


//-----------------------------------6个数码管-----------------------------------------------------------
set_property -dict {PACKAGE_PIN N15  IOSTANDARD LVCMOS33} [get_ports {digitron_out[0]}]
set_property -dict {PACKAGE_PIN R17  IOSTANDARD LVCMOS33} [get_ports {digitron_out[1]}]
set_property -dict {PACKAGE_PIN P16  IOSTANDARD LVCMOS33} [get_ports {digitron_out[2]}]
set_property -dict {PACKAGE_PIN N14 IOSTANDARD LVCMOS33} [get_ports {digitron_out[3]}]
set_property -dict {PACKAGE_PIN N13 IOSTANDARD LVCMOS33} [get_ports {digitron_out[4]}]
set_property -dict {PACKAGE_PIN R16  IOSTANDARD LVCMOS33} [get_ports {digitron_out[5]}]
set_property -dict {PACKAGE_PIN P15  IOSTANDARD LVCMOS33} [get_ports {digitron_out[6]}]
set_property -dict {PACKAGE_PIN P17  IOSTANDARD LVCMOS33} [get_ports {digitron_out[7]}]

set_property -dict {PACKAGE_PIN R14  IOSTANDARD LVCMOS33} [get_ports {digitroncs_out[0]}]
set_property -dict {PACKAGE_PIN R18  IOSTANDARD LVCMOS33} [get_ports {digitroncs_out[1]}]
set_property -dict {PACKAGE_PIN T18  IOSTANDARD LVCMOS33} [get_ports {digitroncs_out[2]}]
set_property -dict {PACKAGE_PIN N17 IOSTANDARD LVCMOS33} [get_ports {digitroncs_out[3]}]

set_property -dict {PACKAGE_PIN P14   IOSTANDARD LVCMOS33} [get_ports {digitron_a[0]}]
set_property -dict {PACKAGE_PIN U18   IOSTANDARD LVCMOS33} [get_ports {digitron_a[1]}]
set_property -dict {PACKAGE_PIN U17   IOSTANDARD LVCMOS33} [get_ports {digitron_a[2]}]
set_property -dict {PACKAGE_PIN AB18 IOSTANDARD LVCMOS33} [get_ports {digitron_a[3]}]

set_property -dict {PACKAGE_PIN AA18 IOSTANDARD LVCMOS33} [get_ports {digitron_b[0]}]
set_property -dict {PACKAGE_PIN W17  IOSTANDARD LVCMOS33} [get_ports {digitron_b[1]}]
set_property -dict {PACKAGE_PIN V17   IOSTANDARD LVCMOS33} [get_ports {digitron_b[2]}]
set_property -dict {PACKAGE_PIN AB20 IOSTANDARD LVCMOS33} [get_ports {digitron_b[3]}]



//----------------------------------------------串口---------------------------------------------
set_property -dict {PACKAGE_PIN Y21 IOSTANDARD LVCMOS33} [get_ports uart_rxd]
set_property -dict {PACKAGE_PIN Y22 IOSTANDARD LVCMOS33} [get_ports uart_txd]



//----------------------------------------------蜂鸣�?-----------------------------------------
set_property -dict {PACKAGE_PIN P20 IOSTANDARD LVCMOS33} [get_ports buzzer]



//--------------------------------------------------------XADC数模转换-------------------
set_property -dict {PACKAGE_PIN J5 IOSTANDARD LVCMOS33} [get_ports ad15p]
set_property -dict {PACKAGE_PIN H5 IOSTANDARD LVCMOS33} [get_ports ad15n]
set_property -dict {PACKAGE_PIN K2 IOSTANDARD LVCMOS33} [get_ports ad7p]
set_property -dict {PACKAGE_PIN J2 IOSTANDARD LVCMOS33} [get_ports ad7n]
set_property -dict {PACKAGE_PIN H2 IOSTANDARD LVCMOS33} [get_ports ad14p]
set_property -dict {PACKAGE_PIN G2 IOSTANDARD LVCMOS33} [get_ports ad14n]
set_property -dict {PACKAGE_PIN K1 IOSTANDARD LVCMOS33} [get_ports ad6p]
set_property -dict {PACKAGE_PIN J1 IOSTANDARD LVCMOS33} [get_ports ad6n]
set_property -dict {PACKAGE_PIN E1 IOSTANDARD LVCMOS33} [get_ports ad5p]
set_property -dict {PACKAGE_PIN D1 IOSTANDARD LVCMOS33} [get_ports ad5n]
set_property -dict {PACKAGE_PIN G1 IOSTANDARD LVCMOS33} [get_ports ad13p]
set_property -dict {PACKAGE_PIN F1 IOSTANDARD LVCMOS33} [get_ports ad13n]
set_property -dict {PACKAGE_PIN B1 IOSTANDARD LVCMOS33} [get_ports ad4p]
set_property -dict {PACKAGE_PIN A1 IOSTANDARD LVCMOS33} [get_ports ad4n]




//--------------------------------------------------------DDR3L-------------------------------------
set_property -dict {PACKAGE_PIN Y3    IOSTANDARD LVCMOS33} [get_ports ddr3l_dqs0_p]
set_property -dict {PACKAGE_PIN AA3 IOSTANDARD LVCMOS33} [get_ports ddr3l_dqs0_n]
set_property -dict {PACKAGE_PIN R3    IOSTANDARD LVCMOS33} [get_ports ddr3l_dqs1_p]
set_property -dict {PACKAGE_PIN R2    IOSTANDARD LVCMOS33} [get_ports ddr3l_dqs1_n]

set_property -dict {PACKAGE_PIN V4   IOSTANDARD LVCMOS33} [get_ports ddr3l_dq0]
set_property -dict {PACKAGE_PIN AB2 IOSTANDARD LVCMOS33} [get_ports ddr3l_dq1]
set_property -dict {PACKAGE_PIN AB3 IOSTANDARD LVCMOS33} [get_ports ddr3l_dq2]
set_property -dict {PACKAGE_PIN AA1 IOSTANDARD LVCMOS33} [get_ports ddr3l_dq3]
set_property -dict {PACKAGE_PIN AA5 IOSTANDARD LVCMOS33} [get_ports ddr3l_dq4]
set_property -dict {PACKAGE_PIN Y4    IOSTANDARD LVCMOS33} [get_ports ddr3l_dq5]
set_property -dict {PACKAGE_PIN AB5 IOSTANDARD LVCMOS33} [get_ports ddr3l_dq6]
set_property -dict {PACKAGE_PIN AA4 IOSTANDARD LVCMOS33} [get_ports ddr3l_dq7]
set_property -dict {PACKAGE_PIN V2    IOSTANDARD LVCMOS33} [get_ports ddr3l_dq8]
set_property -dict {PACKAGE_PIN Y1    IOSTANDARD LVCMOS33} [get_ports ddr3l_dq9]
set_property -dict {PACKAGE_PIN U1    IOSTANDARD LVCMOS33} [get_ports ddr3l_dq10]
set_property -dict {PACKAGE_PIN Y2    IOSTANDARD LVCMOS33} [get_ports ddr3l_dq11]
set_property -dict {PACKAGE_PIN T1    IOSTANDARD LVCMOS33} [get_ports ddr3l_dq12]
set_property -dict {PACKAGE_PIN W1   IOSTANDARD LVCMOS33} [get_ports ddr3l_dq13]
set_property -dict {PACKAGE_PIN U2    IOSTANDARD LVCMOS33} [get_ports ddr3l_dq14]
set_property -dict {PACKAGE_PIN U3    IOSTANDARD LVCMOS33} [get_ports ddr3l_dq15]

set_property -dict {PACKAGE_PIN AA8 IOSTANDARD LVCMOS33} [get_ports ddr3l_a0]
set_property -dict {PACKAGE_PIN U5   IOSTANDARD LVCMOS33} [get_ports ddr3l_a1]
set_property -dict {PACKAGE_PIN Y9    IOSTANDARD LVCMOS33} [get_ports ddr3l_a2]
set_property -dict {PACKAGE_PIN Y8    IOSTANDARD LVCMOS33} [get_ports ddr3l_a3]
set_property -dict {PACKAGE_PIN V5    IOSTANDARD LVCMOS33} [get_ports ddr3l_a4]
set_property -dict {PACKAGE_PIN W7   IOSTANDARD LVCMOS33} [get_ports ddr3l_a5]
set_property -dict {PACKAGE_PIN U6    IOSTANDARD LVCMOS33} [get_ports ddr3l_a6]
set_property -dict {PACKAGE_PIN V7    IOSTANDARD LVCMOS33} [get_ports ddr3l_a7]
set_property -dict {PACKAGE_PIN T5    IOSTANDARD LVCMOS33} [get_ports ddr3l_a8]
set_property -dict {PACKAGE_PIN W9   IOSTANDARD LVCMOS33} [get_ports ddr3l_a9]
set_property -dict {PACKAGE_PIN AA6 IOSTANDARD LVCMOS33} [get_ports ddr3l_a10]
set_property -dict {PACKAGE_PIN T6    IOSTANDARD LVCMOS33} [get_ports ddr3l_a11]
set_property -dict {PACKAGE_PIN Y6    IOSTANDARD LVCMOS33} [get_ports ddr3l_a12]

set_property -dict {PACKAGE_PIN AB8 IOSTANDARD LVCMOS33} [get_ports ddr3l_ba0]
set_property -dict {PACKAGE_PIN W5  IOSTANDARD LVCMOS33} [get_ports ddr3l_ba1]
set_property -dict {PACKAGE_PIN Y7   IOSTANDARD LVCMOS33} [get_ports ddr3l_ba2]

set_property -dict {PACKAGE_PIN AB1 IOSTANDARD LVCMOS33} [get_ports ddr3l_dm0]
set_property -dict {PACKAGE_PIN W2  IOSTANDARD LVCMOS33} [get_ports ddr3l_dm1]

set_property -dict {PACKAGE_PIN AB6 IOSTANDARD LVCMOS33} [get_ports ddr3l_odt]
set_property -dict {PACKAGE_PIN V9   IOSTANDARD LVCMOS33} [get_ports ddr3l_clk_p]
set_property -dict {PACKAGE_PIN V8   IOSTANDARD LVCMOS33} [get_ports ddr3l_clk_n]
set_property -dict {PACKAGE_PIN R4   IOSTANDARD LVCMOS33} [get_ports ddr3l_cke]
set_property -dict {PACKAGE_PIN U7   IOSTANDARD LVCMOS33} [get_ports ddr3l_cs]
set_property -dict {PACKAGE_PIN AB7 IOSTANDARD LVCMOS33} [get_ports ddr3l_ras]
set_property -dict {PACKAGE_PIN W6  IOSTANDARD LVCMOS33} [get_ports ddr3l_we]
set_property -dict {PACKAGE_PIN T3    IOSTANDARD LVCMOS33} [get_ports ddr3l_reset]
set_property -dict {PACKAGE_PIN T4    IOSTANDARD LVCMOS33} [get_ports ddr3l_cas]

# set_property ALLOW_COMBINATORIAL_LOOPS TRUE [get_nets led_pin_OBUF[6]]


































