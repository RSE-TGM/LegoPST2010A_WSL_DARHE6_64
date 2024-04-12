/* Automatically generated.  Do not edit */
/* See the mkopcodeh.awk script for details */
#define OP_ContextPop                           1
#define OP_IntegrityCk                          2
#define OP_DropTrigger                          3
#define OP_DropIndex                            4
#define OP_IdxInsert                            5
#define OP_Delete                               6
#define OP_MoveGt                               7
#define OP_VerifyCookie                         8
#define OP_Push                                 9
#define OP_Dup                                 10
#define OP_Blob                                11
#define OP_FifoWrite                           12
#define OP_IdxGT                               13
#define OP_RowKey                              14
#define OP_IsUnique                            15
#define OP_SetNumColumns                       16
#define OP_Eq                                  76   /* same as TK_EQ       */
#define OP_Expire                              17
#define OP_IdxIsNull                           18
#define OP_NullRow                             19
#define OP_OpenPseudo                          20
#define OP_OpenWrite                           21
#define OP_OpenRead                            22
#define OP_Transaction                         23
#define OP_AutoCommit                          24
#define OP_Negative                            92   /* same as TK_UMINUS   */
#define OP_Pop                                 25
#define OP_Halt                                26
#define OP_Vacuum                              27
#define OP_RowData                             28
#define OP_NotExists                           29
#define OP_MoveLe                              30
#define OP_OpenVirtual                         31
#define OP_SetCookie                           32
#define OP_Variable                            33
#define OP_MemMove                             34
#define OP_LoadAnalysis                        35
#define OP_IdxDelete                           36
#define OP_Sort                                37
#define OP_ResetCount                          38
#define OP_NotNull                             74   /* same as TK_NOTNULL  */
#define OP_Ge                                  80   /* same as TK_GE       */
#define OP_Remainder                           90   /* same as TK_REM      */
#define OP_Divide                              89   /* same as TK_SLASH    */
#define OP_Integer                             39
#define OP_AggStep                             40
#define OP_CreateIndex                         41
#define OP_NewRowid                            42
#define OP_MoveLt                              43
#define OP_Explain                             44
#define OP_And                                 68   /* same as TK_AND      */
#define OP_ShiftLeft                           84   /* same as TK_LSHIFT   */
#define OP_Real                               133   /* same as TK_FLOAT    */
#define OP_Return                              45
#define OP_MemLoad                             46
#define OP_IdxLT                               47
#define OP_Rewind                              48
#define OP_MakeIdxRec                          49
#define OP_Gt                                  77   /* same as TK_GT       */
#define OP_AddImm                              50
#define OP_Subtract                            87   /* same as TK_MINUS    */
#define OP_Null                                51
#define OP_MemNull                             52
#define OP_MemIncr                             53
#define OP_Clear                               54
#define OP_IsNull                              73   /* same as TK_ISNULL   */
#define OP_If                                  55
#define OP_ToBlob                              56
#define OP_Callback                            57
#define OP_AggFinal                            58
#define OP_Last                                59
#define OP_Rowid                               60
#define OP_Sequence                            61
#define OP_NotFound                            62
#define OP_MakeRecord                          63
#define OP_ToText                              64
#define OP_BitAnd                              82   /* same as TK_BITAND   */
#define OP_Add                                 86   /* same as TK_PLUS     */
#define OP_HexBlob                            134   /* same as TK_BLOB     */
#define OP_String                              65
#define OP_Goto                                66
#define OP_MemInt                              70
#define OP_IfMemPos                            71
#define OP_DropTable                           72
#define OP_IdxRowid                            81
#define OP_Insert                              93
#define OP_Column                              96
#define OP_Noop                                97
#define OP_Not                                 69   /* same as TK_NOT      */
#define OP_Le                                  78   /* same as TK_LE       */
#define OP_BitOr                               83   /* same as TK_BITOR    */
#define OP_Multiply                            88   /* same as TK_STAR     */
#define OP_String8                             95   /* same as TK_STRING   */
#define OP_CreateTable                         98
#define OP_Found                               99
#define OP_Distinct                           100
#define OP_Close                              101
#define OP_Statement                          102
#define OP_IfNot                              103
#define OP_ToInt                              104
#define OP_Pull                               105
#define OP_MemMax                             106
#define OP_MemStore                           107
#define OP_Next                               108
#define OP_Prev                               109
#define OP_MoveGe                             110
#define OP_Lt                                  79   /* same as TK_LT       */
#define OP_Ne                                  75   /* same as TK_NE       */
#define OP_MustBeInt                          111
#define OP_ForceInt                           112
#define OP_ShiftRight                          85   /* same as TK_RSHIFT   */
#define OP_CollSeq                            113
#define OP_Gosub                              114
#define OP_ContextPush                        115
#define OP_FifoRead                           116
#define OP_ParseSchema                        117
#define OP_Destroy                            118
#define OP_IdxGE                              119
#define OP_ReadCookie                         120
#define OP_BitNot                              94   /* same as TK_BITNOT   */
#define OP_AbsValue                           121
#define OP_Or                                  67   /* same as TK_OR       */
#define OP_ToNumeric                          122
#define OP_Function                           123
#define OP_Concat                              91   /* same as TK_CONCAT   */
#define OP_Int64                              124

/* The following opcode values are never used */
#define OP_NotUsed_125                        125
#define OP_NotUsed_126                        126
#define OP_NotUsed_127                        127
#define OP_NotUsed_128                        128
#define OP_NotUsed_129                        129
#define OP_NotUsed_130                        130
#define OP_NotUsed_131                        131
#define OP_NotUsed_132                        132

#define NOPUSH_MASK_0 46074
#define NOPUSH_MASK_1 61439
#define NOPUSH_MASK_2 43385
#define NOPUSH_MASK_3 20453
#define NOPUSH_MASK_4 65469
#define NOPUSH_MASK_5 30717
#define NOPUSH_MASK_6 65530
#define NOPUSH_MASK_7 1199
#define NOPUSH_MASK_8 0
#define NOPUSH_MASK_9 0
