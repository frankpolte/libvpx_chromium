/*
 *  Copyright (c) 2010 The WebM project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "vp9/common/vp9_common.h"
#include "vp9/common/vp9_quant_common.h"
#include "vp9/common/vp9_seg_common.h"

#if 1
static const int16_t dc_qlookup[QINDEX_RANGE] = {
  4,       8,    8,    9,   10,   11,   12,   12,
  13,     14,   15,   16,   17,   18,   19,   19,
  20,     21,   22,   23,   24,   25,   26,   26,
  27,     28,   29,   30,   31,   32,   32,   33,
  34,     35,   36,   37,   38,   38,   39,   40,
  41,     42,   43,   43,   44,   45,   46,   47,
  48,     48,   49,   50,   51,   52,   53,   53,
  54,     55,   56,   57,   57,   58,   59,   60,
  61,     62,   62,   63,   64,   65,   66,   66,
  67,     68,   69,   70,   70,   71,   72,   73,
  74,     74,   75,   76,   77,   78,   78,   79,
  80,     81,   81,   82,   83,   84,   85,   85,
  87,     88,   90,   92,   93,   95,   96,   98,
  99,    101,  102,  104,  105,  107,  108,  110,
  111,   113,  114,  116,  117,  118,  120,  121,
  123,   125,  127,  129,  131,  134,  136,  138,
  140,   142,  144,  146,  148,  150,  152,  154,
  156,   158,  161,  164,  166,  169,  172,  174,
  177,   180,  182,  185,  187,  190,  192,  195,
  199,   202,  205,  208,  211,  214,  217,  220,
  223,   226,  230,  233,  237,  240,  243,  247,
  250,   253,  257,  261,  265,  269,  272,  276,
  280,   284,  288,  292,  296,  300,  304,  309,
  313,   317,  322,  326,  330,  335,  340,  344,
  349,   354,  359,  364,  369,  374,  379,  384,
  389,   395,  400,  406,  411,  417,  423,  429,
  435,   441,  447,  454,  461,  467,  475,  482,
  489,   497,  505,  513,  522,  530,  539,  549,
  559,   569,  579,  590,  602,  614,  626,  640,
  654,   668,  684,  700,  717,  736,  755,  775,
  796,   819,  843,  869,  896,  925,  955,  988,
  1022, 1058, 1098, 1139, 1184, 1232, 1282, 1336,
};

#if CONFIG_VP9_HIGH && CONFIG_HIGH_TRANSFORMS && CONFIG_HIGH_QUANT
static const int16_t dc_qlookup_10[QINDEX_RANGE] = {
  4,     8,     9,    10,    11,    12,    13,    14,
  15,    16,    18,    19,    20,    21,    22,    24,
  25,    26,    28,    29,    30,    32,    33,    34,
  36,    37,    39,    40,    42,    43,    45,    46,
  48,    50,    51,    53,    55,    56,    58,    60,
  61,    63,    65,    67,    68,    70,    72,    74,
  76,    78,    79,    81,    83,    85,    87,    89,
  91,    93,    95,    97,    99,   102,   104,   106,
  108,   110,   112,   114,   117,   119,   121,   123,
  126,   128,   130,   133,   135,   137,   140,   142,
  144,   147,   149,   152,   154,   157,   159,   162,
  164,   167,   169,   172,   175,   177,   180,   182,
  187,   191,   195,   200,   204,   209,   213,   218,
  222,   227,   231,   236,   241,   245,   250,   255,
  259,   264,   269,   274,   279,   284,   288,   293,
  298,   305,   312,   318,   325,   332,   339,   346,
  353,   360,   367,   374,   381,   388,   395,   402,
  409,   416,   425,   434,   443,   452,   461,   470,
  479,   488,   497,   506,   516,   525,   534,   545,
  556,   567,   578,   589,   600,   611,   622,   633,
  644,   657,   670,   683,   696,   708,   721,   734,
  747,   760,   774,   789,   803,   818,   832,   847,
  861,   878,   894,   910,   926,   942,   958,   976,
  993,  1011,  1029,  1046,  1064,  1083,  1102,  1121,
  1140,  1160,  1180,  1201,  1222,  1242,  1263,  1285,
  1308,  1330,  1353,  1377,  1401,  1425,  1450,  1476,
  1502,  1528,  1555,  1583,  1612,  1641,  1672,  1703,
  1735,  1768,  1802,  1837,  1874,  1912,  1950,  1991,
  2033,  2076,  2122,  2169,  2219,  2271,  2324,  2381,
  2440,  2503,  2568,  2638,  2711,  2789,  2870,  2957,
  3048,  3145,  3247,  3356,  3470,  3594,  3722,  3861,
  4005,  4161,  4330,  4506,  4696,  4901,  5116,  5347,
};

static const int16_t dc_qlookup_12[QINDEX_RANGE] = {
  4,     9,    10,    12,    13,    15,    17,    19,
  21,    23,    26,    28,    31,    33,    36,    39,
  42,    45,    48,    51,    54,    58,    61,    65,
  68,    72,    76,    80,    84,    88,    93,    97,
  102,   106,   111,   116,   120,   125,   130,   136,
  141,   146,   152,   157,   163,   168,   174,   180,
  186,   192,   198,   205,   211,   217,   224,   231,
  237,   244,   251,   258,   265,   272,   280,   287,
  294,   302,   310,   317,   325,   333,   341,   349,
  357,   365,   374,   382,   391,   399,   408,   417,
  426,   435,   444,   453,   462,   471,   481,   490,
  500,   509,   519,   529,   539,   549,   559,   569,
  584,   600,   615,   631,   647,   664,   680,   696,
  713,   730,   746,   764,   781,   798,   815,   833,
  851,   869,   887,   905,   923,   942,   960,   979,
  998,  1023,  1048,  1073,  1098,  1124,  1150,  1176,
  1202,  1228,  1255,  1281,  1308,  1335,  1362,  1389,
  1417,  1444,  1478,  1512,  1547,  1581,  1616,  1650,
  1685,  1720,  1756,  1791,  1827,  1863,  1899,  1941,
  1983,  2026,  2069,  2112,  2155,  2198,  2241,  2285,
  2329,  2379,  2429,  2479,  2529,  2580,  2631,  2681,
  2732,  2783,  2841,  2898,  2955,  3013,  3071,  3128,
  3186,  3250,  3314,  3378,  3443,  3507,  3571,  3642,
  3712,  3783,  3854,  3924,  3995,  4072,  4149,  4226,
  4303,  4381,  4464,  4548,  4631,  4715,  4799,  4890,
  4980,  5071,  5163,  5260,  5358,  5457,  5556,  5662,
  5768,  5876,  5984,  6099,  6216,  6334,  6459,  6586,
  6715,  6852,  6991,  7132,  7283,  7436,  7593,  7760,
  7930,  8105,  8291,  8483,  8687,  8897,  9114,  9345,
  9584,  9840, 10105, 10390, 10684, 11001, 11329, 11683,
  12051, 12446, 12859, 13303, 13766, 14266, 14787, 15349,
  15937, 16571, 17254, 17970, 18742, 19574, 20447, 21388,
};
#endif

static const int16_t ac_qlookup[QINDEX_RANGE] = {
  4,       8,    9,   10,   11,   12,   13,   14,
  15,     16,   17,   18,   19,   20,   21,   22,
  23,     24,   25,   26,   27,   28,   29,   30,
  31,     32,   33,   34,   35,   36,   37,   38,
  39,     40,   41,   42,   43,   44,   45,   46,
  47,     48,   49,   50,   51,   52,   53,   54,
  55,     56,   57,   58,   59,   60,   61,   62,
  63,     64,   65,   66,   67,   68,   69,   70,
  71,     72,   73,   74,   75,   76,   77,   78,
  79,     80,   81,   82,   83,   84,   85,   86,
  87,     88,   89,   90,   91,   92,   93,   94,
  95,     96,   97,   98,   99,  100,  101,  102,
  104,   106,  108,  110,  112,  114,  116,  118,
  120,   122,  124,  126,  128,  130,  132,  134,
  136,   138,  140,  142,  144,  146,  148,  150,
  152,   155,  158,  161,  164,  167,  170,  173,
  176,   179,  182,  185,  188,  191,  194,  197,
  200,   203,  207,  211,  215,  219,  223,  227,
  231,   235,  239,  243,  247,  251,  255,  260,
  265,   270,  275,  280,  285,  290,  295,  300,
  305,   311,  317,  323,  329,  335,  341,  347,
  353,   359,  366,  373,  380,  387,  394,  401,
  408,   416,  424,  432,  440,  448,  456,  465,
  474,   483,  492,  501,  510,  520,  530,  540,
  550,   560,  571,  582,  593,  604,  615,  627,
  639,   651,  663,  676,  689,  702,  715,  729,
  743,   757,  771,  786,  801,  816,  832,  848,
  864,   881,  898,  915,  933,  951,  969,  988,
  1007, 1026, 1046, 1066, 1087, 1108, 1129, 1151,
  1173, 1196, 1219, 1243, 1267, 1292, 1317, 1343,
  1369, 1396, 1423, 1451, 1479, 1508, 1537, 1567,
  1597, 1628, 1660, 1692, 1725, 1759, 1793, 1828,
};

#if CONFIG_VP9_HIGH && CONFIG_HIGH_TRANSFORMS && CONFIG_HIGH_QUANT
static const int16_t ac_qlookup_10[QINDEX_RANGE] = {
  4,     8,     9,    10,    12,    13,    14,    15,
  17,    18,    19,    21,    22,    23,    25,    26,
  28,    29,    31,    32,    34,    35,    37,    38,
  40,    42,    43,    45,    47,    49,    50,    52,
  54,    56,    58,    60,    62,    64,    66,    68,
  70,    72,    74,    76,    78,    80,    82,    84,
  87,    89,    91,    93,    96,    98,   100,   103,
  105,   108,   110,   112,   115,   117,   120,   123,
  125,   128,   130,   133,   136,   138,   141,   144,
  147,   149,   152,   155,   158,   161,   164,   167,
  170,   173,   176,   179,   182,   185,   188,   191,
  194,   197,   200,   204,   207,   210,   213,   217,
  222,   228,   233,   239,   245,   250,   256,   262,
  268,   274,   279,   285,   292,   298,   304,   310,
  316,   322,   329,   335,   341,   348,   354,   361,
  368,   377,   386,   395,   404,   414,   423,   433,
  442,   452,   461,   471,   481,   491,   501,   511,
  521,   531,   544,   557,   570,   583,   597,   610,
  624,   637,   651,   664,   678,   692,   706,   723,
  740,   757,   775,   792,   809,   827,   845,   863,
  880,   901,   923,   944,   965,   987,  1008,  1030,
  1052,  1074,  1099,  1125,  1150,  1176,  1202,  1228,
  1254,  1284,  1313,  1343,  1373,  1404,  1434,  1468,
  1502,  1536,  1570,  1605,  1640,  1678,  1716,  1755,
  1794,  1833,  1876,  1919,  1962,  2005,  2049,  2097,
  2144,  2192,  2240,  2292,  2344,  2397,  2449,  2506,
  2563,  2620,  2677,  2739,  2800,  2862,  2928,  2995,
  3061,  3132,  3203,  3274,  3349,  3425,  3501,  3582,
  3662,  3743,  3829,  3914,  4004,  4094,  4185,  4280,
  4376,  4476,  4576,  4681,  4786,  4895,  5006,  5120,
  5235,  5355,  5475,  5600,  5725,  5855,  5986,  6121,
  6257,  6398,  6543,  6689,  6839,  6995,  7151,  7312,
};

static const int16_t ac_qlookup_12[QINDEX_RANGE] = {
  4,     9,    11,    12,    14,    16,    18,    21,
  23,    25,    28,    31,    33,    36,    39,    43,
  46,    49,    53,    56,    60,    64,    68,    72,
  76,    81,    85,    90,    94,    99,   104,   109,
  114,   120,   125,   131,   136,   142,   148,   154,
  160,   166,   172,   179,   185,   192,   199,   206,
  213,   220,   227,   235,   242,   250,   258,   265,
  273,   282,   290,   298,   306,   315,   324,   333,
  341,   350,   360,   369,   378,   388,   397,   407,
  417,   427,   437,   447,   457,   468,   478,   489,
  500,   511,   522,   533,   544,   556,   567,   579,
  590,   602,   614,   626,   638,   651,   663,   676,
  695,   715,   734,   755,   775,   795,   816,   837,
  858,   880,   901,   923,   946,   968,   991,  1013,
  1036,  1060,  1083,  1107,  1131,  1155,  1180,  1205,
  1230,  1263,  1297,  1331,  1365,  1400,  1435,  1471,
  1506,  1542,  1579,  1616,  1653,  1691,  1729,  1767,
  1805,  1844,  1893,  1942,  1991,  2041,  2091,  2142,
  2194,  2245,  2298,  2350,  2403,  2457,  2511,  2576,
  2641,  2706,  2773,  2839,  2907,  2975,  3043,  3113,
  3182,  3263,  3345,  3427,  3510,  3593,  3678,  3763,
  3849,  3935,  4033,  4132,  4232,  4333,  4434,  4536,
  4639,  4755,  4871,  4988,  5106,  5226,  5346,  5478,
  5612,  5747,  5883,  6020,  6158,  6309,  6461,  6615,
  6770,  6926,  7095,  7266,  7438,  7611,  7786,  7975,
  8165,  8356,  8549,  8756,  8965,  9175,  9387,  9614,
  9842, 10072, 10303, 10550, 10798, 11048, 11313, 11581,
  11850, 12134, 12421, 12710, 13015, 13321, 13630, 13956,
  14283, 14612, 14959, 15307, 15672, 16040, 16410, 16797,
  17187, 17594, 18004, 18431, 18861, 19309, 19760, 20229,
  20701, 21191, 21684, 22196, 22711, 23244, 23781, 24337,
  24897, 25476, 26074, 26675, 27297, 27938, 28583, 29248,
};
#endif


void vp9_init_quant_tables(void) { }
#else
static int16_t dc_qlookup[QINDEX_RANGE];
static int16_t ac_qlookup[QINDEX_RANGE];

#define ACDC_MIN 8

// TODO(dkovalev) move to common and reuse
static double poly3(double a, double b, double c, double d, double x) {
  return a*x*x*x + b*x*x + c*x + d;
}

void vp9_init_quant_tables() {
  int i, val = 4;

  // A "real" q of 1.0 forces lossless mode.
  // In practice non lossless Q's between 1.0 and 2.0 (represented here by
  // integer values from 5-7 give poor rd results (lower psnr and often
  // larger size than the lossless encode. To block out those "not very useful"
  // values we increment the ac and dc q lookup values by 4 after position 0.
  ac_qlookup[0] = val;
  dc_qlookup[0] = val;
  val += 4;

  for (i = 1; i < QINDEX_RANGE; i++) {
    const int ac_val = val;

    val = (int)(val * 1.01975);
    if (val == ac_val)
      ++val;

    ac_qlookup[i] = (int16_t)ac_val;
    dc_qlookup[i] = (int16_t)MAX(ACDC_MIN, poly3(0.000000305, -0.00065, 0.9,
                                                 0.5, ac_val));
  }
}
#endif

int16_t vp9_dc_quant(int qindex, int delta, vpx_bit_depth_t bit_depth) {
#if CONFIG_VP9_HIGH && CONFIG_HIGH_TRANSFORMS && CONFIG_HIGH_QUANT
  switch (bit_depth) {
    case VPX_BITS_8:
      return dc_qlookup[clamp(qindex + delta, 0, MAXQ)];
    case VPX_BITS_10:
      return dc_qlookup_10[clamp(qindex + delta, 0, MAXQ)];
    case VPX_BITS_12:
      return dc_qlookup_12[clamp(qindex + delta, 0, MAXQ)];
    default:
      assert(0 && "bit_depth should be VPX_BITS_8, VPX_BITS_10 or VPX_BITS_12");
  }
#elif CONFIG_VP9_HIGH && CONFIG_HIGH_TRANSFORMS
  switch (bit_depth) {
    case VPX_BITS_8:
      return dc_qlookup[clamp(qindex + delta, 0, MAXQ)];
    case VPX_BITS_10:
      return dc_qlookup[clamp(qindex + delta, 0, MAXQ)] << 2;
    case VPX_BITS_12:
      return dc_qlookup[clamp(qindex + delta, 0, MAXQ)] << 4;
    default:
      assert(0 && "bit_depth should be VPX_BITS_8, VPX_BITS_10 or VPX_BITS_12");
  }
#else
  (void) bit_depth;
  return dc_qlookup[clamp(qindex + delta, 0, MAXQ)];
#endif
}

int16_t vp9_ac_quant(int qindex, int delta, vpx_bit_depth_t bit_depth) {
#if CONFIG_VP9_HIGH && CONFIG_HIGH_TRANSFORMS && CONFIG_HIGH_QUANT
  switch (bit_depth) {
    case VPX_BITS_8:
      return ac_qlookup[clamp(qindex + delta, 0, MAXQ)];
    case VPX_BITS_10:
      return ac_qlookup_10[clamp(qindex + delta, 0, MAXQ)];
    case VPX_BITS_12:
      return ac_qlookup_12[clamp(qindex + delta, 0, MAXQ)];
    default:
      assert(0 && "bit_depth should be VPX_BITS_8, VPX_BITS_10 or VPX_BITS_12");
  }
#elif CONFIG_VP9_HIGH && CONFIG_HIGH_TRANSFORMS
  switch (bit_depth) {
    case VPX_BITS_8:
      return ac_qlookup[clamp(qindex + delta, 0, MAXQ)];
    case VPX_BITS_10:
      return ac_qlookup[clamp(qindex + delta, 0, MAXQ)] << 2;
    case VPX_BITS_12:
      return ac_qlookup[clamp(qindex + delta, 0, MAXQ)] << 4;
    default:
      assert(0 && "bit_depth should be VPX_BITS_8, VPX_BITS_10 or VPX_BITS_12");
  }
#else
  (void) bit_depth;
  return ac_qlookup[clamp(qindex + delta, 0, MAXQ)];
#endif
}

int vp9_get_qindex(const struct segmentation *seg, int segment_id,
                   int base_qindex, vpx_bit_depth_t bit_depth) {
  if (vp9_segfeature_active(seg, segment_id, SEG_LVL_ALT_Q)) {
    const int data = vp9_get_segdata(seg, segment_id, SEG_LVL_ALT_Q);
    const int seg_qindex = seg->abs_delta == SEGMENT_ABSDATA ?
        data : base_qindex + data;
    return clamp(seg_qindex, 0, MAXQ);
  } else {
    return base_qindex;
  }
}
