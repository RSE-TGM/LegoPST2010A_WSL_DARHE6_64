/**********************************************************************
*
*       C Header:               monituil.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed Jan 22 12:27:57 1997 %
*
**********************************************************************/
/*
   modulo monituil.h
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)monituil.h	5.1
*/
/*
 indici dei widget instanziati: N.B. devono corrispondere a quelle
 presenti nel modulo UIL.
 */
/*
 indici di push buttons di menu
*/
#define k_stato                            1
#define k_initialize                       2
#define k_run                              3
#define k_freeze                           4
#define k_step                             5
#define k_backtrack                        6
#define k_replay                           7
#define k_stop                             8
#define k_quit                             9
#define k_configure                       10
#define k_timescaling                     11
#define k_stepcr                          12
#define k_confcr                          13
#define k_set_ftime                       14
#define k_ci                              15
#define k_load                            16
#define k_save                            17
#define k_edit                            18
#define k_statistics                      19
#define k_input                           20
#define k_go                              21
#define k_tempo_sim                       22
#define k_tempo_sim_val                   23
#define k_timescaling_sim                 24
#define k_timescaling_sim_val             25
#define k_grandezze_mem                   26
#define k_grandezze_mem_val               27
#define k_passo_reg                       28
#define k_passo_reg_val                   29
#define k_tempo_reale                     30
#define k_tempo_reale_val                 31
#define k_tempo_ritardo                   32
#define k_tempo_ritardo_val               33
#define k_tempo_simMB                     34
#define k_tempo_simMB_val                 35
#define k_spazio_dsk                      36
#define k_spazio_dsk_val                  37
#define k_stato_sim                       38
#define k_stato_sim_val                   39
#define k_messaggi                        40
#define k_statistica_dialog               41
#define k_statistica_dialog_fine          42
#define k_statistica_window               43
#define k_timescaling_dialog              44
#define k_timescaling_dialog_ok           45
#define k_timescaling_dialog_annulla      46
#define k_timescaling_dialog_label        47
#define k_timescaling_dialog_text         48
#define k_stepcr_dialog                   49
#define k_stepcr_dialog_ok                50
#define k_stepcr_dialog_annulla           51
#define k_stepcr_dialog_label             52
#define k_stepcr_dialog_text              53
#define k_salva_file_dialog               54
#define k_salva_file_dialog_ok            55
#define k_salva_file_dialog_annulla       56
#define k_salva_file_dialog_label1        57
#define k_elenco_variabili_dialog         58
#define k_elenco_variabili_dialog_ok      59
#define k_elenco_variabili                60
#define k_elenco_variabili_sel            61
#define k_elenco_modelli                  62
#define k_elenco_blocchi                  63
#define k_elenco_variabili_aggiungi       64
#define k_elenco_variabili_elimina        65
#define k_elenco_variabili_carica         66
#define k_elenco_variabili_salva          67
#define k_elenco_variabili_annulla        68
#define k_elenco_variabili_dialog_label   69
#define k_salva_file_dialog_text          70
#define k_elenco_variabili_descr          71
#define k_elenco_variabili_autore         72
#define k_elenco_variabili_versione       73
#define k_elenco_variabili_modello        74
#define k_selezione_file_dialog           75
#define k_elenco_variabili_label          76
#define k_elenco_variabili_sel_label      77
#define k_elenco_variabili_cerca_avanti   78
#define k_elenco_variabili_cerca_ind      79
#define k_elenco_variabili_text_cerca     80
#define k_caricamento_dialog              81
#define k_caricamento_label               82
#define k_caricamento_lista               83
#define k_caricamento_ok                  84
#define k_caricamento_annulla             85
#define k_editing_dialog                  86
#define k_editing_label                   87
#define k_editing_fine                    88
#define k_editing_cancella                89
#define k_editing_lista                   90
#define k_scrittura_dialog                91
#define k_scrittura_label                 92
#define k_scrittura_text                  93
#define k_scrittura_ok                    94
#define k_scrittura_annulla               95
#define k_elenco_pert_dialog              96
#define k_elenco_pert_ok                  97
#define k_elenco_pert_fine                98
#define k_elenco_ingressi                 99
#define k_elenco_modelli_pert            100
#define k_elenco_blocchi_pert            101
#define k_elenco_pert_dialog_label       102
#define k_elenco_ingressi_label          103
#define k_elenco_pert_cerca_avanti       104
#define k_elenco_pert_cerca_ind          105
#define k_elenco_pert_text_cerca         106
#define k_staz_dialog                    107
#define k_staz_label                     108
#define k_staz_lista                     109
#define k_staz_ok                        110
#define k_staz_annulla                   111
#define k_staz_button                    112
#define k_conflg                         113
#define k_elenco_variabili_nu_var_sel    114
#define k_clear                          115
#define k_inputstat	                 116
#define k_inputstat_quit                 117
#define k_inputstat_dialog               118
#define k_inputstat_label_1              119
#define k_inputstat_label_2              120
#define k_inputstat_lista_1              121
#define k_inputstat_lista_2              122
#define k_inputstat_del                  123
#define k_set_ftime_dialog               124
#define k_set_ftime_dialog_ok            125
#define k_set_ftime_dialog_annulla       126
#define k_set_ftime_dialog_label         127
#define k_set_ftime_dialog_text          128
#define k_about                          129
#define k_stepscaling		         130
#define k_stepscaling_sim                131
#define k_stepscaling_sim_val            132
#define k_endtime_sim                    133
#define k_endtime_sim_val                134
#define k_stepscaling_dialog             135
#define k_stepscaling_dialog_ok          136
#define k_stepscaling_dialog_annulla     137
#define k_stepscaling_dialog_label       138
#define k_stepscaling_dialog_text        139
#define k_timescaling_dialog_max         140
#define k_editpert                       141
#define k_editpert_quit                  142
#define k_editpert_dialog                143
#define k_editpert_label_1               144
#define k_editpert_label_2               145
#define k_editpert_lista_1               146
#define k_editpert_lista_2               147
#define k_editpert_del                   148
#define k_editpert_mod                   149
#define k_clear_list        	         150
#define k_clear_list_popup               151
#define k_confcrall                      152
#define k_editpert_del_all               153
#define k_backtrack_dialog               154
#define k_menu_backtrack_label           155
#define k_step_bt                        156
#define k_limiti_bt_val                  157
#define k_lastrec_bt_val                 158
#define k_caricamento_lista_bt           159
#define k_reset_bt                       160
#define k_bt_help                        161
#define k_bt_configure                   162
#define k_bt_conf                        163
#define k_restart_bt                     164
#define k_modo_bt_val                    165
#define k_direz_bt_val                   166
#define k_stato_bt                       167
#define k_bt_indietro                    168
#define k_bt_avanti                      169
#define k_bt_automatico                  170
#define k_bt_manuale                     171
#define k_lastload_bt_val                172
#define k_nextstep_bt_val                173
#define k_allineamento_dialog            174
#define k_caricamento_lista_comp         175
#define k_override_comp                  176
#define k_help                           177
#define k_bt_help_load                   178
#define k_bt_help_ok                     179
#define k_bt_help_exit                   180
#define k_bt_help_procedure              181
#define k_stop_replay                    182
#define k_malf_menu_entry                183
#define k_malf                           184
#define k_frem                           185
#define k_malf_dialog                    186
#define k_frem_dialog                    187
#define k_window_malf                    188
#define k_window_frem                    189
#define k_data_button		         190
#define k_data_dialog		         191
#define k_data_dialog_label              192
#define k_elenco_modelli_modat           193
#define k_elenco_blocchi_modat           194
#define k_data_dialog_ok                 195
#define k_data_dialog_canc               196
#define k_data_scrolled                  197
#define k_data_rowcol                    198
#define k_editing_modify                 199
#define k_azzera_cascade		 200
#define k_graphics		         201
#define k_procstat			 202
                         

#define MAX_WIDGETS           250
