**********************************************************************
** Visual Studio 2026 Developer Command Prompt v18.11.1
** Copyright (c) 2026 Microsoft Corporation
**********************************************************************
[vcvarsall.bat] Environment initialized for: 'x64'
[Compiling with MSVC...]
Microsoft (R) C/C++ Optimizing Compiler Version 19.51.36260 for x64
Copyright (C) Microsoft Corporation.  All rights reserved.

benchmark.cpp
Microsoft (R) Incremental Linker Version 14.51.36260.0
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:bench_msvc.exe
benchmark.obj
[Running Benchmark...]
[+] CPU Environment Stabilized:
    - EfficiencyClass : 1 (P-Core)
    - Processor Group : 0
    - Logical Core Bit: 0x4
    - SMT Isolated    : Yes
Objects: 1000000 | Poly Types: 16

| relative |               ns/op |                op/s |    err% |     total | C++ Dispatch Matrix Benchmark
|---------:|--------------------:|--------------------:|--------:|----------:|:------------------------------
|   100.0% |                3.03 |      330,045,348.23 |    1.0% |      0.35 | `01 Baseline: Direct Call (AoS) | Mono | 64B_Line (64B) [Seq]`
|    20.0% |               15.11 |       66,170,271.99 |    0.4% |      1.71 | `01 Baseline: Direct Call (AoS) | Mono | 64B_Line (64B) [Rnd]`
|   100.8% |                3.01 |      332,632,587.35 |    0.9% |      0.34 | `01 Baseline: Direct Call (AoS) | PolySorted | 64B_Line (64B) [Seq]`
|    28.2% |               10.74 |       93,067,639.70 |    0.3% |      1.23 | `01 Baseline: Direct Call (AoS) | PolySorted | 64B_Line (64B) [Rnd]`
|   102.3% |                2.96 |      337,611,622.84 |    0.9% |      0.34 | `01 Baseline: Direct Call (AoS) | PolyRnd | 64B_Line (64B) [Seq]`
|    20.4% |               14.83 |       67,449,928.97 |    0.2% |      1.69 | `01 Baseline: Direct Call (AoS) | PolyRnd | 64B_Line (64B) [Rnd]`
|   317.9% |                0.95 |    1,049,163,816.44 |    2.0% |      0.11 | `01 Baseline: Direct Call (AoS) | PolyRnd | 16B_Compact (8B) [Seq]`
|   114.4% |                2.65 |      377,709,790.02 |    0.4% |      0.31 | `01 Baseline: Direct Call (AoS) | PolyRnd | 16B_Compact (8B) [Rnd]`
|   109.0% |                2.78 |      359,642,694.98 |    1.1% |      0.32 | `01 Baseline: Direct Call (AoS) | PolyRnd | 60B_Split (60B) [Seq]`
|    20.8% |               14.55 |       68,726,538.48 |    0.6% |      1.66 | `01 Baseline: Direct Call (AoS) | PolyRnd | 60B_Split (60B) [Rnd]`
|    41.1% |                7.37 |      135,623,908.12 |    0.8% |      0.84 | `01 Baseline: Direct Call (AoS) | PolyRnd | 256B_Heavy (256B) [Seq]`
|    12.3% |               24.67 |       40,532,946.25 |    0.6% |      2.82 | `01 Baseline: Direct Call (AoS) | PolyRnd | 256B_Heavy (256B) [Rnd]`
|   362.0% |                0.84 |    1,194,885,888.40 |    0.3% |      0.10 | `01 Baseline: SoA (Data Oriented) [Seq]`
|    39.5% |                7.67 |      130,340,710.62 |    0.6% |      0.88 | `02 Virtual: Polymorphic | Mono | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    17.3% |               17.47 |       57,242,011.21 |    0.9% |      2.01 | `02 Virtual: Polymorphic | Mono | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    38.5% |                7.87 |      127,099,192.70 |    0.6% |      0.90 | `02 Virtual: Polymorphic | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    19.2% |               15.82 |       63,208,578.04 |    1.4% |      1.80 | `02 Virtual: Polymorphic | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    24.5% |               12.37 |       80,850,809.24 |    0.3% |      1.41 | `02 Virtual: Polymorphic | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    11.3% |               26.81 |       37,298,219.55 |    0.7% |      3.06 | `02 Virtual: Polymorphic | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    29.4% |               10.30 |       97,104,736.60 |    0.2% |      1.17 | `02 Virtual: Polymorphic | PolyRnd | HeapCompact | 64B_Line (64B) [Seq]`
|    11.5% |               26.46 |       37,794,617.38 |    0.5% |      3.01 | `02 Virtual: Polymorphic | PolyRnd | HeapCompact | 64B_Line (64B) [Rnd]`
|    29.1% |               10.40 |       96,167,543.09 |    0.4% |      1.18 | `02 Virtual: Polymorphic | PolyRnd | HeapJitter | 64B_Line (64B) [Seq]`
|    11.2% |               26.99 |       37,053,891.41 |    2.2% |      3.05 | `02 Virtual: Polymorphic | PolyRnd | HeapJitter | 64B_Line (64B) [Rnd]`
|    36.9% |                8.22 |      121,689,833.71 |    0.9% |      0.94 | `02 Virtual: Polymorphic | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Seq]`
|    11.5% |               26.31 |       38,001,351.83 |    3.1% |      2.97 | `02 Virtual: Polymorphic | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Rnd]`
|    27.3% |               11.11 |       90,027,530.42 |    0.1% |      1.27 | `02 Virtual: Polymorphic | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Seq]`
|    11.9% |               25.53 |       39,172,682.73 |    0.7% |      2.92 | `02 Virtual: Polymorphic | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Rnd]`
|    22.5% |               13.46 |       74,305,418.49 |    0.2% |      1.53 | `02 Virtual: Polymorphic | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Seq]`
|    11.1% |               27.41 |       36,488,556.01 |    0.2% |      3.12 | `02 Virtual: Polymorphic | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Rnd]`
|    16.3% |               18.60 |       53,776,820.82 |    1.3% |      2.11 | `02.1 Hierarchy: Deep Chain | Mono | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|     3.6% |               84.81 |       11,790,542.27 |    0.8% |      9.70 | `02.1 Hierarchy: Deep Chain | Mono | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    16.1% |               18.86 |       53,033,760.94 |    0.6% |      2.14 | `02.1 Hierarchy: Deep Chain | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|     4.0% |               74.85 |       13,359,464.45 |    0.4% |      8.53 | `02.1 Hierarchy: Deep Chain | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|     8.5% |               35.54 |       28,139,214.96 |    0.2% |      4.05 | `02.1 Hierarchy: Deep Chain | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|     3.2% |               95.04 |       10,521,475.26 |    0.4% |     10.83 | `02.1 Hierarchy: Deep Chain | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    11.3% |               26.93 |       37,130,259.06 |    1.2% |      3.06 | `02.1 Hierarchy: Deep Chain | PolyRnd | HeapCompact | 64B_Line (64B) [Seq]`
|     3.3% |               92.63 |       10,795,438.88 |    0.4% |     10.54 | `02.1 Hierarchy: Deep Chain | PolyRnd | HeapCompact | 64B_Line (64B) [Rnd]`
|    11.3% |               26.85 |       37,247,886.13 |    0.7% |      3.06 | `02.1 Hierarchy: Deep Chain | PolyRnd | HeapJitter | 64B_Line (64B) [Seq]`
|     3.3% |               93.08 |       10,743,632.53 |    0.5% |     10.70 | `02.1 Hierarchy: Deep Chain | PolyRnd | HeapJitter | 64B_Line (64B) [Rnd]`
|    13.2% |               22.94 |       43,586,089.06 |    0.6% |      2.60 | `02.1 Hierarchy: Deep Chain | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Seq]`
|     3.6% |               85.06 |       11,755,954.84 |    0.4% |      9.68 | `02.1 Hierarchy: Deep Chain | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Rnd]`
|    10.6% |               28.47 |       35,130,797.12 |    0.4% |      3.24 | `02.1 Hierarchy: Deep Chain | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Seq]`
|     3.3% |               92.20 |       10,845,429.98 |    0.4% |     10.55 | `02.1 Hierarchy: Deep Chain | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Rnd]`
|     7.5% |               40.59 |       24,639,515.67 |    0.5% |      4.63 | `02.1 Hierarchy: Deep Chain | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Seq]`
|     3.1% |               97.87 |       10,217,146.82 |    0.6% |     11.14 | `02.1 Hierarchy: Deep Chain | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Rnd]`
|    20.4% |               14.86 |       67,301,514.37 |    0.1% |      1.69 | `02.2 Hierarchy: Multi Inherit (Thunks) | Mono | HeapTrash1to1 | 64B_Line (320B) [Seq]`
|    14.6% |               20.82 |       48,032,542.05 |    0.3% |      2.38 | `02.2 Hierarchy: Multi Inherit (Thunks) | Mono | HeapTrash1to1 | 64B_Line (320B) [Rnd]`
|    20.4% |               14.84 |       67,364,620.27 |    0.3% |      1.69 | `02.2 Hierarchy: Multi Inherit (Thunks) | PolySorted | HeapTrash1to1 | 64B_Line (320B) [Seq]`
|    17.5% |               17.33 |       57,690,519.55 |    0.4% |      1.99 | `02.2 Hierarchy: Multi Inherit (Thunks) | PolySorted | HeapTrash1to1 | 64B_Line (320B) [Rnd]`
|    18.1% |               16.72 |       59,805,773.28 |    0.1% |      1.90 | `02.2 Hierarchy: Multi Inherit (Thunks) | PolyRnd | HeapTrash1to1 | 64B_Line (320B) [Seq]`
|    10.2% |               29.64 |       33,740,446.97 |    0.1% |      3.38 | `02.2 Hierarchy: Multi Inherit (Thunks) | PolyRnd | HeapTrash1to1 | 64B_Line (320B) [Rnd]`
|    22.7% |               13.32 |       75,070,698.93 |    0.1% |      1.52 | `02.2 Hierarchy: Multi Inherit (Thunks) | PolyRnd | HeapCompact | 64B_Line (320B) [Seq]`
|    10.3% |               29.44 |       33,964,776.26 |    0.2% |      3.35 | `02.2 Hierarchy: Multi Inherit (Thunks) | PolyRnd | HeapCompact | 64B_Line (320B) [Rnd]`
|    22.6% |               13.42 |       74,543,317.35 |    0.1% |      1.53 | `02.2 Hierarchy: Multi Inherit (Thunks) | PolyRnd | HeapJitter | 64B_Line (320B) [Seq]`
|    10.3% |               29.51 |       33,883,768.88 |    0.2% |      3.37 | `02.2 Hierarchy: Multi Inherit (Thunks) | PolyRnd | HeapJitter | 64B_Line (320B) [Rnd]`
|    21.1% |               14.35 |       69,665,535.76 |    0.3% |      1.64 | `02.2 Hierarchy: Multi Inherit (Thunks) | PolyRnd | HeapTrash1to1 | 16B_Compact (264B) [Seq]`
|    10.7% |               28.19 |       35,477,481.97 |    0.6% |      3.22 | `02.2 Hierarchy: Multi Inherit (Thunks) | PolyRnd | HeapTrash1to1 | 16B_Compact (264B) [Rnd]`
|    20.9% |               14.52 |       68,885,040.51 |    0.3% |      1.66 | `02.2 Hierarchy: Multi Inherit (Thunks) | PolyRnd | HeapTrash1to1 | 60B_Split (264B) [Seq]`
|    10.8% |               27.94 |       35,785,313.17 |    0.4% |      3.19 | `02.2 Hierarchy: Multi Inherit (Thunks) | PolyRnd | HeapTrash1to1 | 60B_Split (264B) [Rnd]`
|    18.0% |               16.87 |       59,278,130.68 |    0.1% |      1.92 | `02.2 Hierarchy: Multi Inherit (Thunks) | PolyRnd | HeapTrash1to1 | 256B_Heavy (320B) [Seq]`
|    10.1% |               29.87 |       33,478,833.74 |    0.1% |      3.41 | `02.2 Hierarchy: Multi Inherit (Thunks) | PolyRnd | HeapTrash1to1 | 256B_Heavy (320B) [Rnd]`
|    37.7% |                8.04 |      124,323,988.31 |    0.3% |      0.92 | `02.3 Hierarchy: Virtual Diamond | Mono | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    14.0% |               21.63 |       46,223,798.17 |    0.2% |      2.46 | `02.3 Hierarchy: Virtual Diamond | Mono | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    36.9% |                8.20 |      121,950,393.29 |    0.3% |      0.94 | `02.3 Hierarchy: Virtual Diamond | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    17.1% |               17.69 |       56,538,926.39 |    0.6% |      2.03 | `02.3 Hierarchy: Virtual Diamond | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    22.8% |               13.27 |       75,352,238.47 |    0.1% |      1.51 | `02.3 Hierarchy: Virtual Diamond | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    10.5% |               28.93 |       34,571,261.05 |    0.3% |      3.30 | `02.3 Hierarchy: Virtual Diamond | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    27.8% |               10.90 |       91,735,445.77 |    0.4% |      1.24 | `02.3 Hierarchy: Virtual Diamond | PolyRnd | HeapCompact | 64B_Line (64B) [Seq]`
|    10.7% |               28.41 |       35,195,820.23 |    0.3% |      3.24 | `02.3 Hierarchy: Virtual Diamond | PolyRnd | HeapCompact | 64B_Line (64B) [Rnd]`
|    27.7% |               10.93 |       91,478,707.57 |    0.2% |      1.25 | `02.3 Hierarchy: Virtual Diamond | PolyRnd | HeapJitter | 64B_Line (64B) [Seq]`
|    10.6% |               28.59 |       34,981,837.87 |    0.9% |      3.25 | `02.3 Hierarchy: Virtual Diamond | PolyRnd | HeapJitter | 64B_Line (64B) [Rnd]`
|    26.5% |               11.43 |       87,461,230.08 |    0.3% |      1.30 | `02.3 Hierarchy: Virtual Diamond | PolyRnd | HeapTrash1to1 | 16B_Compact (40B) [Seq]`
|    10.5% |               28.76 |       34,771,166.13 |    0.1% |      3.28 | `02.3 Hierarchy: Virtual Diamond | PolyRnd | HeapTrash1to1 | 16B_Compact (40B) [Rnd]`
|    22.6% |               13.43 |       74,463,675.38 |    0.3% |      1.53 | `02.3 Hierarchy: Virtual Diamond | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Seq]`
|    10.3% |               29.42 |       33,989,493.42 |    0.3% |      3.35 | `02.3 Hierarchy: Virtual Diamond | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Rnd]`
|    16.7% |               18.09 |       55,279,560.83 |    0.3% |      2.07 | `02.3 Hierarchy: Virtual Diamond | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Seq]`
|     9.7% |               31.30 |       31,952,958.43 |    0.2% |      3.57 | `02.3 Hierarchy: Virtual Diamond | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Rnd]`
|    38.3% |                7.92 |      126,250,617.58 |    0.3% |      0.91 | `02.4 Hierarchy: Fat VTable (64 methods) | Mono | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    17.1% |               17.72 |       56,445,075.06 |    0.3% |      2.02 | `02.4 Hierarchy: Fat VTable (64 methods) | Mono | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    38.2% |                7.94 |      125,975,102.87 |    0.4% |      0.91 | `02.4 Hierarchy: Fat VTable (64 methods) | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    19.6% |               15.47 |       64,621,538.57 |    0.8% |      1.77 | `02.4 Hierarchy: Fat VTable (64 methods) | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    24.0% |               12.65 |       79,057,633.01 |    0.2% |      1.45 | `02.4 Hierarchy: Fat VTable (64 methods) | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    11.5% |               26.40 |       37,883,720.65 |    0.3% |      3.01 | `02.4 Hierarchy: Fat VTable (64 methods) | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    29.1% |               10.40 |       96,132,096.81 |    0.1% |      1.19 | `02.4 Hierarchy: Fat VTable (64 methods) | PolyRnd | HeapCompact | 64B_Line (64B) [Seq]`
|    11.7% |               26.00 |       38,462,475.37 |    0.3% |      2.97 | `02.4 Hierarchy: Fat VTable (64 methods) | PolyRnd | HeapCompact | 64B_Line (64B) [Rnd]`
|    28.8% |               10.52 |       95,042,880.18 |    0.3% |      1.20 | `02.4 Hierarchy: Fat VTable (64 methods) | PolyRnd | HeapJitter | 64B_Line (64B) [Seq]`
|    11.6% |               26.21 |       38,160,547.15 |    0.3% |      2.99 | `02.4 Hierarchy: Fat VTable (64 methods) | PolyRnd | HeapJitter | 64B_Line (64B) [Rnd]`
|    35.8% |                8.47 |      118,008,198.62 |    0.3% |      0.97 | `02.4 Hierarchy: Fat VTable (64 methods) | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Seq]`
|    12.8% |               23.76 |       42,091,647.88 |    0.2% |      2.71 | `02.4 Hierarchy: Fat VTable (64 methods) | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Rnd]`
|    26.9% |               11.25 |       88,852,212.67 |    0.3% |      1.29 | `02.4 Hierarchy: Fat VTable (64 methods) | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Seq]`
|    11.8% |               25.66 |       38,973,126.32 |    0.3% |      2.94 | `02.4 Hierarchy: Fat VTable (64 methods) | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Rnd]`
|    22.5% |               13.48 |       74,188,672.68 |    0.2% |      1.54 | `02.4 Hierarchy: Fat VTable (64 methods) | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Seq]`
|    11.2% |               26.95 |       37,112,462.39 |    0.2% |      3.08 | `02.4 Hierarchy: Fat VTable (64 methods) | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Rnd]`
|   103.5% |                2.93 |      341,756,629.07 |    0.7% |      0.33 | `03 Variant: std::visit | Mono | 64B_Line (64B) [Seq]`
|    22.0% |               13.74 |       72,759,800.64 |    0.8% |      1.57 | `03 Variant: std::visit | Mono | 64B_Line (64B) [Rnd]`
|   103.2% |                2.94 |      340,480,758.83 |    0.5% |      0.34 | `03 Variant: std::visit | PolySorted | 64B_Line (64B) [Seq]`
|    24.0% |               12.62 |       79,250,527.76 |    0.5% |      1.44 | `03 Variant: std::visit | PolySorted | 64B_Line (64B) [Rnd]`
|    33.0% |                9.18 |      108,948,048.49 |    0.3% |      1.05 | `03 Variant: std::visit | PolyRnd | 64B_Line (64B) [Seq]`
|    13.7% |               22.12 |       45,204,264.51 |    0.5% |      2.52 | `03 Variant: std::visit | PolyRnd | 64B_Line (64B) [Rnd]`
|    39.4% |                7.70 |      129,878,188.69 |    0.3% |      0.88 | `03 Variant: std::visit | PolyRnd | 16B_Compact (8B) [Seq]`
|    25.7% |               11.78 |       84,867,934.18 |    0.6% |      1.35 | `03 Variant: std::visit | PolyRnd | 16B_Compact (8B) [Rnd]`
|    32.8% |                9.24 |      108,237,855.87 |    0.3% |      1.05 | `03 Variant: std::visit | PolyRnd | 60B_Split (60B) [Seq]`
|    13.9% |               21.72 |       46,036,474.39 |    0.1% |      2.48 | `03 Variant: std::visit | PolyRnd | 60B_Split (60B) [Rnd]`
|    21.0% |               14.44 |       69,253,403.50 |    0.1% |      1.65 | `03 Variant: std::visit | PolyRnd | 256B_Heavy (256B) [Seq]`
|    10.8% |               28.02 |       35,692,581.23 |    0.1% |      3.20 | `03 Variant: std::visit | PolyRnd | 256B_Heavy (256B) [Rnd]`
|    38.3% |                7.92 |      126,316,764.55 |    0.6% |      0.91 | `04 Erasure: Fat Ptr (Trait Object) | Mono | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    13.7% |               22.11 |       45,231,327.64 |    0.5% |      2.52 | `04 Erasure: Fat Ptr (Trait Object) | Mono | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    37.9% |                7.99 |      125,229,239.08 |    0.1% |      0.91 | `04 Erasure: Fat Ptr (Trait Object) | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    16.3% |               18.63 |       53,685,188.16 |    0.7% |      2.12 | `04 Erasure: Fat Ptr (Trait Object) | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    28.4% |               10.66 |       93,792,957.91 |    0.5% |      1.21 | `04 Erasure: Fat Ptr (Trait Object) | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    13.3% |               22.82 |       43,813,913.55 |    0.2% |      2.60 | `04 Erasure: Fat Ptr (Trait Object) | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    33.9% |                8.94 |      111,806,577.25 |    0.5% |      1.02 | `04 Erasure: Fat Ptr (Trait Object) | PolyRnd | HeapCompact | 64B_Line (64B) [Seq]`
|    13.5% |               22.41 |       44,624,768.17 |    0.6% |      2.55 | `04 Erasure: Fat Ptr (Trait Object) | PolyRnd | HeapCompact | 64B_Line (64B) [Rnd]`
|    33.5% |                9.05 |      110,542,513.18 |    0.3% |      1.03 | `04 Erasure: Fat Ptr (Trait Object) | PolyRnd | HeapJitter | 64B_Line (64B) [Seq]`
|    13.5% |               22.52 |       44,397,632.51 |    0.4% |      2.56 | `04 Erasure: Fat Ptr (Trait Object) | PolyRnd | HeapJitter | 64B_Line (64B) [Rnd]`
|    48.1% |                6.30 |      158,837,830.31 |    0.3% |      0.72 | `04 Erasure: Fat Ptr (Trait Object) | PolyRnd | HeapTrash1to1 | 16B_Compact (8B) [Seq]`
|    15.4% |               19.70 |       50,758,538.78 |    0.6% |      2.25 | `04 Erasure: Fat Ptr (Trait Object) | PolyRnd | HeapTrash1to1 | 16B_Compact (8B) [Rnd]`
|    32.0% |                9.48 |      105,482,155.83 |    0.7% |      1.08 | `04 Erasure: Fat Ptr (Trait Object) | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Seq]`
|    13.5% |               22.51 |       44,421,463.74 |    0.3% |      2.57 | `04 Erasure: Fat Ptr (Trait Object) | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Rnd]`
|    27.0% |               11.22 |       89,137,099.40 |    0.2% |      1.28 | `04 Erasure: Fat Ptr (Trait Object) | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Seq]`
|    13.0% |               23.32 |       42,876,530.98 |    0.5% |      2.66 | `04 Erasure: Fat Ptr (Trait Object) | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Rnd]`
|    39.6% |                7.64 |      130,828,506.15 |    0.3% |      0.87 | `04.1 Erasure: C Struct* + FuncPtr | Mono | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    13.8% |               21.88 |       45,707,129.28 |    0.4% |      2.49 | `04.1 Erasure: C Struct* + FuncPtr | Mono | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    38.9% |                7.79 |      128,334,779.24 |    0.3% |      0.89 | `04.1 Erasure: C Struct* + FuncPtr | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    16.6% |               18.26 |       54,767,868.10 |    0.5% |      2.08 | `04.1 Erasure: C Struct* + FuncPtr | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    29.3% |               10.34 |       96,735,447.36 |    0.3% |      1.18 | `04.1 Erasure: C Struct* + FuncPtr | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    13.4% |               22.61 |       44,237,291.04 |    0.2% |      2.59 | `04.1 Erasure: C Struct* + FuncPtr | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    35.4% |                8.56 |      116,792,034.26 |    0.2% |      0.98 | `04.1 Erasure: C Struct* + FuncPtr | PolyRnd | HeapCompact | 64B_Line (64B) [Seq]`
|    13.8% |               21.98 |       45,498,886.19 |    0.1% |      2.51 | `04.1 Erasure: C Struct* + FuncPtr | PolyRnd | HeapCompact | 64B_Line (64B) [Rnd]`
|    35.1% |                8.62 |      116,010,267.68 |    0.6% |      0.98 | `04.1 Erasure: C Struct* + FuncPtr | PolyRnd | HeapJitter | 64B_Line (64B) [Seq]`
|    13.8% |               21.96 |       45,544,623.95 |    0.4% |      2.51 | `04.1 Erasure: C Struct* + FuncPtr | PolyRnd | HeapJitter | 64B_Line (64B) [Rnd]`
|    52.9% |                5.73 |      174,452,413.26 |    0.6% |      0.65 | `04.1 Erasure: C Struct* + FuncPtr | PolyRnd | HeapTrash1to1 | 16B_Compact (8B) [Seq]`
|    15.5% |               19.52 |       51,217,094.22 |    0.2% |      2.23 | `04.1 Erasure: C Struct* + FuncPtr | PolyRnd | HeapTrash1to1 | 16B_Compact (8B) [Rnd]`
|    33.1% |                9.14 |      109,386,132.32 |    0.2% |      1.04 | `04.1 Erasure: C Struct* + FuncPtr | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Seq]`
|    13.6% |               22.21 |       45,032,337.19 |    0.1% |      2.53 | `04.1 Erasure: C Struct* + FuncPtr | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Rnd]`
|    28.1% |               10.79 |       92,662,890.55 |    0.2% |      1.23 | `04.1 Erasure: C Struct* + FuncPtr | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Seq]`
|    13.2% |               22.90 |       43,665,251.51 |    0.3% |      2.61 | `04.1 Erasure: C Struct* + FuncPtr | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Rnd]`
|   102.3% |                2.96 |      337,666,722.94 |    0.8% |      0.34 | `05 CRTP: Simple | Mono | 64B_Line (64B) [Seq]`
|    21.3% |               14.20 |       70,408,706.90 |    0.7% |      1.62 | `05 CRTP: Simple | Mono | 64B_Line (64B) [Rnd]`
|   102.5% |                2.96 |      338,202,748.32 |    0.8% |      0.34 | `05 CRTP: Simple | PolySorted | 64B_Line (64B) [Seq]`
|    23.6% |               12.82 |       78,031,159.40 |    0.2% |      1.45 | `05 CRTP: Simple | PolySorted | 64B_Line (64B) [Rnd]`
|   101.6% |                2.98 |      335,254,803.51 |    0.8% |      0.34 | `05 CRTP: Simple | PolyRnd | 64B_Line (64B) [Seq]`
|    21.5% |               14.07 |       71,068,322.72 |    0.3% |      1.61 | `05 CRTP: Simple | PolyRnd | 64B_Line (64B) [Rnd]`
|   324.2% |                0.93 |    1,069,997,926.88 |    0.5% |      0.11 | `05 CRTP: Simple | PolyRnd | 16B_Compact (8B) [Seq]`
|   115.5% |                2.62 |      381,072,787.14 |    0.5% |      0.30 | `05 CRTP: Simple | PolyRnd | 16B_Compact (8B) [Rnd]`
|   107.7% |                2.81 |      355,504,994.85 |    0.3% |      0.32 | `05 CRTP: Simple | PolyRnd | 60B_Split (60B) [Seq]`
|    21.1% |               14.38 |       69,559,183.00 |    0.4% |      1.64 | `05 CRTP: Simple | PolyRnd | 60B_Split (60B) [Rnd]`
|    34.8% |                8.70 |      114,916,111.24 |    0.6% |      0.99 | `05 CRTP: Simple | PolyRnd | 256B_Heavy (256B) [Seq]`
|    16.6% |               18.21 |       54,908,195.11 |    0.1% |      2.09 | `05 CRTP: Simple | PolyRnd | 256B_Heavy (256B) [Rnd]`
|   102.4% |                2.96 |      337,991,989.59 |    0.8% |      0.34 | `05.1 CRTP: Wide Mixin | Mono | 64B_Line (64B) [Seq]`
|    23.7% |               12.79 |       78,189,101.32 |    0.7% |      1.45 | `05.1 CRTP: Wide Mixin | Mono | 64B_Line (64B) [Rnd]`
|   102.6% |                2.95 |      338,556,395.53 |    1.0% |      0.34 | `05.1 CRTP: Wide Mixin | PolySorted | 64B_Line (64B) [Seq]`
|    23.8% |               12.71 |       78,677,724.68 |    1.7% |      1.45 | `05.1 CRTP: Wide Mixin | PolySorted | 64B_Line (64B) [Rnd]`
|   102.9% |                2.94 |      339,610,851.25 |    1.4% |      0.34 | `05.1 CRTP: Wide Mixin | PolyRnd | 64B_Line (64B) [Seq]`
|    22.7% |               13.37 |       74,791,518.64 |    2.6% |      1.54 | `05.1 CRTP: Wide Mixin | PolyRnd | 64B_Line (64B) [Rnd]`
|   322.5% |                0.94 |    1,064,515,927.04 |    0.2% |      0.11 | `05.1 CRTP: Wide Mixin | PolyRnd | 16B_Compact (4B) [Seq]`
|   139.6% |                2.17 |      460,627,211.69 |    0.7% |      0.25 | `05.1 CRTP: Wide Mixin | PolyRnd | 16B_Compact (4B) [Rnd]`
|   107.1% |                2.83 |      353,617,730.39 |    0.8% |      0.32 | `05.1 CRTP: Wide Mixin | PolyRnd | 60B_Split (60B) [Seq]`
|    23.9% |               12.68 |       78,892,724.83 |    0.4% |      1.45 | `05.1 CRTP: Wide Mixin | PolyRnd | 60B_Split (60B) [Rnd]`
|    41.4% |                7.32 |      136,569,110.80 |    0.8% |      0.84 | `05.1 CRTP: Wide Mixin | PolyRnd | 256B_Heavy (256B) [Seq]`
|    19.7% |               15.41 |       64,901,797.50 |    0.5% |      1.76 | `05.1 CRTP: Wide Mixin | PolyRnd | 256B_Heavy (256B) [Rnd]`
|   103.8% |                2.92 |      342,731,800.94 |    1.0% |      0.33 | `07.1 Wrappers: std::function (In-Place SBO) | Mono | 64B_Line (64B) [Seq]`
|    17.3% |               17.55 |       56,988,022.12 |    0.3% |      2.00 | `07.1 Wrappers: std::function (In-Place SBO) | Mono | 64B_Line (64B) [Rnd]`
|   103.0% |                2.94 |      340,005,227.58 |    0.5% |      0.34 | `07.1 Wrappers: std::function (In-Place SBO) | PolySorted | 64B_Line (64B) [Seq]`
|    21.6% |               14.04 |       71,246,045.84 |    0.4% |      1.61 | `07.1 Wrappers: std::function (In-Place SBO) | PolySorted | 64B_Line (64B) [Rnd]`
|    33.5% |                9.03 |      110,688,726.01 |    0.4% |      1.03 | `07.1 Wrappers: std::function (In-Place SBO) | PolyRnd | 64B_Line (64B) [Seq]`
|    11.6% |               26.13 |       38,273,208.51 |    1.4% |      2.95 | `07.1 Wrappers: std::function (In-Place SBO) | PolyRnd | 64B_Line (64B) [Rnd]`
|    32.6% |                9.30 |      107,538,136.61 |    1.3% |      1.06 | `07.1 Wrappers: std::function (In-Place SBO) | PolyRnd | 16B_Compact (64B) [Seq]`
|    12.3% |               24.63 |       40,604,608.03 |    0.5% |      2.81 | `07.1 Wrappers: std::function (In-Place SBO) | PolyRnd | 16B_Compact (64B) [Rnd]`
|    32.9% |                9.20 |      108,745,366.33 |    0.5% |      1.05 | `07.1 Wrappers: std::function (In-Place SBO) | PolyRnd | 60B_Split (64B) [Seq]`
|    12.4% |               24.49 |       40,838,929.63 |    0.3% |      2.79 | `07.1 Wrappers: std::function (In-Place SBO) | PolyRnd | 60B_Split (64B) [Rnd]`
|    33.2% |                9.13 |      109,564,560.00 |    0.4% |      1.04 | `07.1 Wrappers: std::function (In-Place SBO) | PolyRnd | 256B_Heavy (64B) [Seq]`
|    12.2% |               24.79 |       40,336,710.69 |    0.3% |      2.81 | `07.1 Wrappers: std::function (In-Place SBO) | PolyRnd | 256B_Heavy (64B) [Rnd]`
|    51.3% |                5.91 |      169,218,885.62 |    0.3% |      0.67 | `07.2 Wrappers: std::function (Payload-Scaled) | Mono | 64B_Line (64B) [Seq]`
|     9.9% |               30.53 |       32,752,979.65 |    0.5% |      3.47 | `07.2 Wrappers: std::function (Payload-Scaled) | Mono | 64B_Line (64B) [Rnd]`
|    50.9% |                5.96 |      167,874,273.36 |    0.2% |      0.68 | `07.2 Wrappers: std::function (Payload-Scaled) | PolySorted | 64B_Line (64B) [Seq]`
|    11.0% |               27.67 |       36,141,016.46 |    0.1% |      3.17 | `07.2 Wrappers: std::function (Payload-Scaled) | PolySorted | 64B_Line (64B) [Rnd]`
|    25.8% |               11.75 |       85,100,674.10 |    0.3% |      1.35 | `07.2 Wrappers: std::function (Payload-Scaled) | PolyRnd | 64B_Line (64B) [Seq]`
|     7.7% |               39.17 |       25,528,703.44 |    0.4% |      4.46 | `07.2 Wrappers: std::function (Payload-Scaled) | PolyRnd | 64B_Line (64B) [Rnd]`
|    33.3% |                9.10 |      109,845,125.70 |    0.3% |      1.04 | `07.2 Wrappers: std::function (Payload-Scaled) | PolyRnd | 16B_Compact (64B) [Seq]`
|    12.4% |               24.41 |       40,972,744.16 |    0.2% |      2.80 | `07.2 Wrappers: std::function (Payload-Scaled) | PolyRnd | 16B_Compact (64B) [Rnd]`
|    25.7% |               11.78 |       84,917,757.15 |    0.8% |      1.34 | `07.2 Wrappers: std::function (Payload-Scaled) | PolyRnd | 60B_Split (64B) [Seq]`
|     7.7% |               39.12 |       25,559,497.40 |    0.1% |      4.46 | `07.2 Wrappers: std::function (Payload-Scaled) | PolyRnd | 60B_Split (64B) [Rnd]`
|    22.8% |               13.31 |       75,137,195.82 |    0.1% |      1.52 | `07.2 Wrappers: std::function (Payload-Scaled) | PolyRnd | 256B_Heavy (64B) [Seq]`
|     7.5% |               40.13 |       24,918,187.73 |    0.2% |      4.58 | `07.2 Wrappers: std::function (Payload-Scaled) | PolyRnd | 256B_Heavy (64B) [Rnd]`
|    38.8% |                7.80 |      128,123,216.95 |    0.7% |      0.89 | `07.3 Wrappers: FuncRef (2-ptr) | Mono | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    13.1% |               23.08 |       43,327,504.18 |    0.6% |      2.64 | `07.3 Wrappers: FuncRef (2-ptr) | Mono | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    38.3% |                7.90 |      126,533,604.87 |    0.2% |      0.90 | `07.3 Wrappers: FuncRef (2-ptr) | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    15.7% |               19.26 |       51,929,741.66 |    0.7% |      2.20 | `07.3 Wrappers: FuncRef (2-ptr) | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    27.6% |               10.98 |       91,112,119.89 |    0.3% |      1.25 | `07.3 Wrappers: FuncRef (2-ptr) | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    12.9% |               23.53 |       42,490,787.29 |    0.5% |      2.68 | `07.3 Wrappers: FuncRef (2-ptr) | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    33.5% |                9.04 |      110,607,845.41 |    0.6% |      1.03 | `07.3 Wrappers: FuncRef (2-ptr) | PolyRnd | HeapCompact | 64B_Line (64B) [Seq]`
|    12.9% |               23.40 |       42,731,573.08 |    0.6% |      2.67 | `07.3 Wrappers: FuncRef (2-ptr) | PolyRnd | HeapCompact | 64B_Line (64B) [Rnd]`
|    33.4% |                9.07 |      110,280,265.04 |    0.7% |      1.04 | `07.3 Wrappers: FuncRef (2-ptr) | PolyRnd | HeapJitter | 64B_Line (64B) [Seq]`
|    12.9% |               23.51 |       42,529,611.24 |    0.7% |      2.68 | `07.3 Wrappers: FuncRef (2-ptr) | PolyRnd | HeapJitter | 64B_Line (64B) [Rnd]`
|    49.6% |                6.11 |      163,565,822.16 |    0.1% |      0.70 | `07.3 Wrappers: FuncRef (2-ptr) | PolyRnd | HeapTrash1to1 | 16B_Compact (8B) [Seq]`
|    14.9% |               20.27 |       49,332,547.08 |    0.7% |      2.33 | `07.3 Wrappers: FuncRef (2-ptr) | PolyRnd | HeapTrash1to1 | 16B_Compact (8B) [Rnd]`
|    31.3% |                9.68 |      103,303,450.66 |    0.4% |      1.10 | `07.3 Wrappers: FuncRef (2-ptr) | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Seq]`
|    12.7% |               23.84 |       41,939,985.28 |    0.2% |      2.72 | `07.3 Wrappers: FuncRef (2-ptr) | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Rnd]`
|    26.5% |               11.44 |       87,428,254.19 |    0.5% |      1.31 | `07.3 Wrappers: FuncRef (2-ptr) | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Seq]`
|    12.2% |               24.82 |       40,285,655.51 |    0.5% |      2.84 | `07.3 Wrappers: FuncRef (2-ptr) | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Rnd]`
|   105.0% |                2.88 |      346,681,947.86 |    0.9% |      0.33 | `07.4 Wrappers: SBO Type Erasure | Mono | 64B_Line (64B) [Seq]`
|    23.6% |               12.83 |       77,956,621.82 |    0.8% |      1.47 | `07.4 Wrappers: SBO Type Erasure | Mono | 64B_Line (64B) [Rnd]`
|   105.9% |                2.86 |      349,387,339.02 |    0.4% |      0.33 | `07.4 Wrappers: SBO Type Erasure | PolySorted | 64B_Line (64B) [Seq]`
|    25.1% |               12.08 |       82,804,891.49 |    0.9% |      1.38 | `07.4 Wrappers: SBO Type Erasure | PolySorted | 64B_Line (64B) [Rnd]`
|    44.5% |                6.81 |      146,857,299.68 |    0.5% |      0.78 | `07.4 Wrappers: SBO Type Erasure | PolyRnd | 64B_Line (64B) [Seq]`
|    16.1% |               18.87 |       53,004,774.41 |    0.3% |      2.15 | `07.4 Wrappers: SBO Type Erasure | PolyRnd | 64B_Line (64B) [Rnd]`
|    60.3% |                5.02 |      199,016,114.09 |    0.2% |      0.57 | `07.4 Wrappers: SBO Type Erasure | PolyRnd | 16B_Compact (16B) [Seq]`
|    29.6% |               10.25 |       97,555,153.09 |    0.5% |      1.16 | `07.4 Wrappers: SBO Type Erasure | PolyRnd | 16B_Compact (16B) [Rnd]`
|    46.2% |                6.55 |      152,561,325.17 |    0.5% |      0.75 | `07.4 Wrappers: SBO Type Erasure | PolyRnd | 60B_Split (60B) [Seq]`
|    16.7% |               18.13 |       55,148,799.12 |    0.5% |      2.07 | `07.4 Wrappers: SBO Type Erasure | PolyRnd | 60B_Split (60B) [Rnd]`
|    29.8% |               10.17 |       98,283,060.46 |    0.1% |      1.16 | `07.4 Wrappers: SBO Type Erasure | PolyRnd | 256B_Heavy (256B) [Seq]`
|    12.8% |               23.61 |       42,348,477.15 |    0.4% |      2.70 | `07.4 Wrappers: SBO Type Erasure | PolyRnd | 256B_Heavy (256B) [Rnd]`
|    40.0% |                7.57 |      132,081,785.04 |    0.4% |      0.86 | `08.1 Pointers: std::unique_ptr | Mono | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    17.2% |               17.60 |       56,828,334.86 |    0.7% |      2.01 | `08.1 Pointers: std::unique_ptr | Mono | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    39.2% |                7.74 |      129,259,578.32 |    0.5% |      0.89 | `08.1 Pointers: std::unique_ptr | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    19.5% |               15.52 |       64,443,693.40 |    2.0% |      1.78 | `08.1 Pointers: std::unique_ptr | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    24.6% |               12.31 |       81,207,527.27 |    0.1% |      1.41 | `08.1 Pointers: std::unique_ptr | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    11.4% |               26.66 |       37,502,823.74 |    0.3% |      3.04 | `08.1 Pointers: std::unique_ptr | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    29.6% |               10.23 |       97,751,148.58 |    0.0% |      1.17 | `08.1 Pointers: std::unique_ptr | PolyRnd | HeapCompact | 64B_Line (64B) [Seq]`
|    11.7% |               25.95 |       38,528,685.81 |    0.4% |      2.96 | `08.1 Pointers: std::unique_ptr | PolyRnd | HeapCompact | 64B_Line (64B) [Rnd]`
|    29.4% |               10.30 |       97,108,674.89 |    0.1% |      1.17 | `08.1 Pointers: std::unique_ptr | PolyRnd | HeapJitter | 64B_Line (64B) [Seq]`
|    11.6% |               26.12 |       38,286,705.66 |    0.5% |      3.00 | `08.1 Pointers: std::unique_ptr | PolyRnd | HeapJitter | 64B_Line (64B) [Rnd]`
|    37.2% |                8.14 |      122,834,322.51 |    0.7% |      0.93 | `08.1 Pointers: std::unique_ptr | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Seq]`
|    12.7% |               23.94 |       41,771,977.74 |    0.7% |      2.73 | `08.1 Pointers: std::unique_ptr | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Rnd]`
|    27.6% |               10.96 |       91,230,165.80 |    0.3% |      1.25 | `08.1 Pointers: std::unique_ptr | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Seq]`
|    11.6% |               26.13 |       38,263,259.36 |    0.2% |      2.99 | `08.1 Pointers: std::unique_ptr | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Rnd]`
|    22.4% |               13.53 |       73,930,883.32 |    0.4% |      1.54 | `08.1 Pointers: std::unique_ptr | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Seq]`
|    11.1% |               27.37 |       36,537,775.01 |    0.6% |      3.13 | `08.1 Pointers: std::unique_ptr | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Rnd]`
|    37.0% |                8.19 |      122,094,258.40 |    0.2% |      0.94 | `08.2 Pointers: std::shared_ptr | Mono | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    12.9% |               23.42 |       42,697,374.62 |    0.6% |      2.70 | `08.2 Pointers: std::shared_ptr | Mono | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    35.4% |                8.55 |      116,908,814.05 |    0.3% |      0.97 | `08.2 Pointers: std::shared_ptr | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    15.4% |               19.67 |       50,837,410.78 |    1.4% |      2.24 | `08.2 Pointers: std::shared_ptr | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    21.6% |               14.04 |       71,243,507.94 |    0.1% |      1.60 | `08.2 Pointers: std::shared_ptr | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|     9.9% |               30.51 |       32,771,400.91 |    0.2% |      3.48 | `08.2 Pointers: std::shared_ptr | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    25.5% |               11.89 |       84,128,970.70 |    0.4% |      1.35 | `08.2 Pointers: std::shared_ptr | PolyRnd | HeapCompact | 64B_Line (64B) [Seq]`
|    10.1% |               29.87 |       33,479,552.18 |    0.2% |      3.40 | `08.2 Pointers: std::shared_ptr | PolyRnd | HeapCompact | 64B_Line (64B) [Rnd]`
|    25.5% |               11.90 |       84,057,920.85 |    0.7% |      1.36 | `08.2 Pointers: std::shared_ptr | PolyRnd | HeapJitter | 64B_Line (64B) [Seq]`
|    10.1% |               29.88 |       33,467,650.17 |    0.4% |      3.41 | `08.2 Pointers: std::shared_ptr | PolyRnd | HeapJitter | 64B_Line (64B) [Rnd]`
|    28.9% |               10.48 |       95,437,999.98 |    0.4% |      1.20 | `08.2 Pointers: std::shared_ptr | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Seq]`
|    10.5% |               28.87 |       34,638,954.93 |    0.4% |      3.30 | `08.2 Pointers: std::shared_ptr | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Rnd]`
|    24.9% |               12.17 |       82,160,281.36 |    0.2% |      1.39 | `08.2 Pointers: std::shared_ptr | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Seq]`
|    10.1% |               29.90 |       33,448,682.51 |    0.3% |      3.41 | `08.2 Pointers: std::shared_ptr | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Rnd]`
|    19.7% |               15.35 |       65,133,340.98 |    0.3% |      1.75 | `08.2 Pointers: std::shared_ptr | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Seq]`
|     9.9% |               30.75 |       32,515,517.07 |    0.3% |      3.51 | `08.2 Pointers: std::shared_ptr | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Rnd]`
|   106.1% |                2.86 |      350,029,031.82 |    0.5% |      0.33 | `08.3 Pointers: Member Ptr (Non-Virtual) | Mono | 64B_Line (64B) [Seq]`
|    24.3% |               12.46 |       80,244,926.40 |    0.4% |      1.42 | `08.3 Pointers: Member Ptr (Non-Virtual) | Mono | 64B_Line (64B) [Rnd]`
|   106.1% |                2.85 |      350,270,876.14 |    0.5% |      0.33 | `08.3 Pointers: Member Ptr (Non-Virtual) | PolySorted | 64B_Line (64B) [Seq]`
|    26.5% |               11.45 |       87,369,055.63 |    0.5% |      1.31 | `08.3 Pointers: Member Ptr (Non-Virtual) | PolySorted | 64B_Line (64B) [Rnd]`
|    44.9% |                6.75 |      148,105,225.06 |    0.3% |      0.77 | `08.3 Pointers: Member Ptr (Non-Virtual) | PolyRnd | 64B_Line (64B) [Seq]`
|    16.0% |               18.97 |       52,713,472.51 |    0.4% |      2.16 | `08.3 Pointers: Member Ptr (Non-Virtual) | PolyRnd | 64B_Line (64B) [Rnd]`
|    58.0% |                5.23 |      191,374,417.29 |    0.5% |      0.60 | `08.3 Pointers: Member Ptr (Non-Virtual) | PolyRnd | 16B_Compact (16B) [Seq]`
|    28.7% |               10.54 |       94,882,421.70 |    0.8% |      1.20 | `08.3 Pointers: Member Ptr (Non-Virtual) | PolyRnd | 16B_Compact (16B) [Rnd]`
|    45.1% |                6.71 |      149,002,576.75 |    0.5% |      0.77 | `08.3 Pointers: Member Ptr (Non-Virtual) | PolyRnd | 60B_Split (60B) [Seq]`
|    16.9% |               17.91 |       55,826,936.50 |    0.1% |      2.05 | `08.3 Pointers: Member Ptr (Non-Virtual) | PolyRnd | 60B_Split (60B) [Rnd]`
|    30.1% |               10.06 |       99,366,044.64 |    0.2% |      1.15 | `08.3 Pointers: Member Ptr (Non-Virtual) | PolyRnd | 256B_Heavy (256B) [Seq]`
|    13.4% |               22.65 |       44,147,072.08 |    0.2% |      2.59 | `08.3 Pointers: Member Ptr (Non-Virtual) | PolyRnd | 256B_Heavy (256B) [Rnd]`
|    40.3% |                7.51 |      133,095,142.32 |    0.1% |      0.86 | `08.4 Pointers: Member Ptr (Virtual vcall) | Mono | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    17.3% |               17.55 |       56,978,325.45 |    1.7% |      1.99 | `08.4 Pointers: Member Ptr (Virtual vcall) | Mono | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    39.4% |                7.69 |      130,013,353.14 |    0.3% |      0.88 | `08.4 Pointers: Member Ptr (Virtual vcall) | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    19.1% |               15.85 |       63,100,745.39 |    2.0% |      1.81 | `08.4 Pointers: Member Ptr (Virtual vcall) | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    22.6% |               13.41 |       74,577,987.30 |    0.1% |      1.53 | `08.4 Pointers: Member Ptr (Virtual vcall) | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    11.4% |               26.61 |       37,581,772.65 |    0.7% |      3.04 | `08.4 Pointers: Member Ptr (Virtual vcall) | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    28.4% |               10.67 |       93,729,341.64 |    0.4% |      1.22 | `08.4 Pointers: Member Ptr (Virtual vcall) | PolyRnd | HeapCompact | 64B_Line (64B) [Seq]`
|    11.6% |               26.13 |       38,275,552.40 |    0.3% |      2.98 | `08.4 Pointers: Member Ptr (Virtual vcall) | PolyRnd | HeapCompact | 64B_Line (64B) [Rnd]`
|    28.2% |               10.76 |       92,947,408.81 |    0.1% |      1.23 | `08.4 Pointers: Member Ptr (Virtual vcall) | PolyRnd | HeapJitter | 64B_Line (64B) [Seq]`
|    11.7% |               25.93 |       38,559,687.70 |    0.4% |      2.96 | `08.4 Pointers: Member Ptr (Virtual vcall) | PolyRnd | HeapJitter | 64B_Line (64B) [Rnd]`
|    34.5% |                8.79 |      113,767,341.52 |    0.2% |      1.01 | `08.4 Pointers: Member Ptr (Virtual vcall) | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Seq]`
|    12.7% |               23.90 |       41,836,649.85 |    0.3% |      2.72 | `08.4 Pointers: Member Ptr (Virtual vcall) | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Rnd]`
|    25.2% |               12.00 |       83,307,605.98 |    0.8% |      1.37 | `08.4 Pointers: Member Ptr (Virtual vcall) | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Seq]`
|    11.7% |               25.85 |       38,689,359.27 |    0.3% |      2.95 | `08.4 Pointers: Member Ptr (Virtual vcall) | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Rnd]`
|    21.0% |               14.41 |       69,384,696.51 |    0.2% |      1.64 | `08.4 Pointers: Member Ptr (Virtual vcall) | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Seq]`
|    11.2% |               27.12 |       36,873,079.86 |    0.5% |      3.09 | `08.4 Pointers: Member Ptr (Virtual vcall) | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Rnd]`
|    42.1% |                7.20 |      138,825,003.68 |    0.2% |      0.82 | `09.1 Predictor: Final Devirt (Direct Call Only) | Mono | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    17.8% |               17.04 |       58,690,997.42 |    1.2% |      1.95 | `09.1 Predictor: Final Devirt (Direct Call Only) | Mono | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    42.0% |                7.22 |      138,465,009.48 |    0.5% |      0.82 | `09.1 Predictor: Final Devirt (Direct Call Only) | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    21.3% |               14.19 |       70,452,070.21 |    0.4% |      1.62 | `09.1 Predictor: Final Devirt (Direct Call Only) | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    42.0% |                7.21 |      138,654,844.65 |    0.1% |      0.82 | `09.1 Predictor: Final Devirt (Direct Call Only) | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    18.0% |               16.85 |       59,348,754.25 |    0.3% |      1.94 | `09.1 Predictor: Final Devirt (Direct Call Only) | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    56.4% |                5.37 |      186,265,062.63 |    0.4% |      0.61 | `09.1 Predictor: Final Devirt (Direct Call Only) | PolyRnd | HeapCompact | 64B_Line (64B) [Seq]`
|    18.2% |               16.68 |       59,950,560.77 |    1.4% |      1.90 | `09.1 Predictor: Final Devirt (Direct Call Only) | PolyRnd | HeapCompact | 64B_Line (64B) [Rnd]`
|    54.9% |                5.52 |      181,122,233.36 |    0.9% |      0.63 | `09.1 Predictor: Final Devirt (Direct Call Only) | PolyRnd | HeapJitter | 64B_Line (64B) [Seq]`
|    18.3% |               16.52 |       60,548,663.50 |    0.3% |      1.89 | `09.1 Predictor: Final Devirt (Direct Call Only) | PolyRnd | HeapJitter | 64B_Line (64B) [Rnd]`
|    81.4% |                3.72 |      268,679,975.28 |    0.6% |      0.42 | `09.1 Predictor: Final Devirt (Direct Call Only) | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Seq]`
|    19.4% |               15.60 |       64,103,000.70 |    0.6% |      1.78 | `09.1 Predictor: Final Devirt (Direct Call Only) | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Rnd]`
|    49.2% |                6.16 |      162,290,394.80 |    0.8% |      0.71 | `09.1 Predictor: Final Devirt (Direct Call Only) | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Seq]`
|    18.2% |               16.69 |       59,914,537.90 |    0.6% |      1.90 | `09.1 Predictor: Final Devirt (Direct Call Only) | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Rnd]`
|    41.1% |                7.37 |      135,644,719.35 |    0.5% |      0.84 | `09.1 Predictor: Final Devirt (Direct Call Only) | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Seq]`
|    16.9% |               17.96 |       55,685,419.45 |    1.1% |      2.05 | `09.1 Predictor: Final Devirt (Direct Call Only) | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Rnd]`
|    42.8% |                7.07 |      141,368,981.88 |    0.3% |      0.81 | `09.2 Predictor: Final Devirt (Inline Enabled) | Mono | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    18.9% |               16.03 |       62,401,511.14 |    0.9% |      1.85 | `09.2 Predictor: Final Devirt (Inline Enabled) | Mono | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    42.8% |                7.08 |      141,143,658.84 |    0.3% |      0.81 | `09.2 Predictor: Final Devirt (Inline Enabled) | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    22.1% |               13.72 |       72,899,757.97 |    1.0% |      1.57 | `09.2 Predictor: Final Devirt (Inline Enabled) | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    42.8% |                7.07 |      141,350,636.75 |    0.2% |      0.81 | `09.2 Predictor: Final Devirt (Inline Enabled) | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    18.2% |               16.64 |       60,086,319.30 |    1.8% |      1.89 | `09.2 Predictor: Final Devirt (Inline Enabled) | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    56.6% |                5.35 |      186,850,499.88 |    0.6% |      0.61 | `09.2 Predictor: Final Devirt (Inline Enabled) | PolyRnd | HeapCompact | 64B_Line (64B) [Seq]`
|    19.1% |               15.88 |       62,966,542.73 |    1.0% |      1.82 | `09.2 Predictor: Final Devirt (Inline Enabled) | PolyRnd | HeapCompact | 64B_Line (64B) [Rnd]`
|    55.9% |                5.42 |      184,387,311.69 |    0.2% |      0.62 | `09.2 Predictor: Final Devirt (Inline Enabled) | PolyRnd | HeapJitter | 64B_Line (64B) [Seq]`
|    19.0% |               15.93 |       62,787,383.08 |    0.9% |      1.83 | `09.2 Predictor: Final Devirt (Inline Enabled) | PolyRnd | HeapJitter | 64B_Line (64B) [Rnd]`
|    83.0% |                3.65 |      274,039,235.57 |    0.1% |      0.41 | `09.2 Predictor: Final Devirt (Inline Enabled) | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Seq]`
|    20.0% |               15.13 |       66,087,956.46 |    0.4% |      1.73 | `09.2 Predictor: Final Devirt (Inline Enabled) | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Rnd]`
|    50.0% |                6.06 |      164,921,410.10 |    0.5% |      0.69 | `09.2 Predictor: Final Devirt (Inline Enabled) | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Seq]`
|    19.0% |               15.98 |       62,579,324.18 |    0.8% |      1.83 | `09.2 Predictor: Final Devirt (Inline Enabled) | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Rnd]`
|    41.8% |                7.26 |      137,824,070.33 |    0.4% |      0.83 | `09.2 Predictor: Final Devirt (Inline Enabled) | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Seq]`
|    17.7% |               17.10 |       58,494,469.35 |    0.4% |      1.95 | `09.2 Predictor: Final Devirt (Inline Enabled) | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Rnd]`
|   104.6% |                2.90 |      345,308,338.76 |    0.5% |      0.33 | `09.3 Predictor: Manual Switch | Mono | 64B_Line (64B) [Seq]`
|    21.3% |               14.24 |       70,221,398.71 |    1.1% |      1.65 | `09.3 Predictor: Manual Switch | Mono | 64B_Line (64B) [Rnd]`
|   103.5% |                2.93 |      341,568,940.00 |    0.3% |      0.33 | `09.3 Predictor: Manual Switch | PolySorted | 64B_Line (64B) [Seq]`
|    23.7% |               12.77 |       78,322,067.19 |    0.6% |      1.47 | `09.3 Predictor: Manual Switch | PolySorted | 64B_Line (64B) [Rnd]`
|    32.9% |                9.22 |      108,456,340.90 |    0.4% |      1.05 | `09.3 Predictor: Manual Switch | PolyRnd | 64B_Line (64B) [Seq]`
|    13.5% |               22.52 |       44,398,401.66 |    0.4% |      2.57 | `09.3 Predictor: Manual Switch | PolyRnd | 64B_Line (64B) [Rnd]`
|    40.1% |                7.56 |      132,256,711.83 |    0.3% |      0.86 | `09.3 Predictor: Manual Switch | PolyRnd | 16B_Compact (8B) [Seq]`
|    25.1% |               12.07 |       82,818,783.30 |    0.4% |      1.38 | `09.3 Predictor: Manual Switch | PolyRnd | 16B_Compact (8B) [Rnd]`
|    33.8% |                8.97 |      111,517,281.83 |    0.2% |      1.02 | `09.3 Predictor: Manual Switch | PolyRnd | 60B_Split (60B) [Seq]`
|    13.4% |               22.55 |       44,344,533.75 |    0.1% |      2.57 | `09.3 Predictor: Manual Switch | PolyRnd | 60B_Split (60B) [Rnd]`
|    21.7% |               13.96 |       71,621,769.65 |    0.1% |      1.59 | `09.3 Predictor: Manual Switch | PolyRnd | 256B_Heavy (256B) [Seq]`
|    11.1% |               27.41 |       36,486,378.88 |    0.1% |      3.12 | `09.3 Predictor: Manual Switch | PolyRnd | 256B_Heavy (256B) [Rnd]`
|    81.2% |                3.73 |      267,989,166.93 |    0.6% |      0.43 | `10.1 Hash: std::unordered_map | Mono | 64B_Line (64B) [Seq]`
|    11.7% |               25.94 |       38,548,062.29 |    0.4% |      2.95 | `10.1 Hash: std::unordered_map | Mono | 64B_Line (64B) [Rnd]`
|    81.3% |                3.72 |      268,484,755.94 |    0.2% |      0.43 | `10.1 Hash: std::unordered_map | PolySorted | 64B_Line (64B) [Seq]`
|    15.1% |               20.05 |       49,880,924.88 |    0.1% |      2.28 | `10.1 Hash: std::unordered_map | PolySorted | 64B_Line (64B) [Rnd]`
|    25.0% |               12.11 |       82,553,125.36 |    0.1% |      1.38 | `10.1 Hash: std::unordered_map | PolyRnd | 64B_Line (64B) [Seq]`
|     8.4% |               35.87 |       27,881,690.32 |    0.2% |      4.09 | `10.1 Hash: std::unordered_map | PolyRnd | 64B_Line (64B) [Rnd]`
|    27.8% |               10.91 |       91,653,882.86 |    0.4% |      1.24 | `10.1 Hash: std::unordered_map | PolyRnd | 16B_Compact (8B) [Seq]`
|    21.1% |               14.34 |       69,713,403.84 |    0.3% |      1.64 | `10.1 Hash: std::unordered_map | PolyRnd | 16B_Compact (8B) [Rnd]`
|    25.9% |               11.71 |       85,383,607.20 |    0.4% |      1.34 | `10.1 Hash: std::unordered_map | PolyRnd | 60B_Split (60B) [Seq]`
|     8.6% |               35.30 |       28,329,605.04 |    0.5% |      4.02 | `10.1 Hash: std::unordered_map | PolyRnd | 60B_Split (60B) [Rnd]`
|    17.0% |               17.80 |       56,186,867.03 |    0.2% |      2.03 | `10.1 Hash: std::unordered_map | PolyRnd | 256B_Heavy (256B) [Seq]`
|     7.0% |               43.30 |       23,092,370.10 |    0.1% |      4.94 | `10.1 Hash: std::unordered_map | PolyRnd | 256B_Heavy (256B) [Rnd]`
|    98.8% |                3.07 |      325,985,617.51 |    1.4% |      0.35 | `10.2 Hash: Compile-Time Perfect Hash | Mono | 64B_Line (64B) [Seq]`
|    18.3% |               16.57 |       60,343,346.54 |    0.3% |      1.90 | `10.2 Hash: Compile-Time Perfect Hash | Mono | 64B_Line (64B) [Rnd]`
|    92.3% |                3.28 |      304,505,540.10 |    3.2% |      0.37 | `10.2 Hash: Compile-Time Perfect Hash | PolySorted | 64B_Line (64B) [Seq]`
|    20.2% |               15.02 |       66,569,800.21 |    0.9% |      1.72 | `10.2 Hash: Compile-Time Perfect Hash | PolySorted | 64B_Line (64B) [Rnd]`
|    34.8% |                8.70 |      114,950,984.90 |    0.4% |      0.99 | `10.2 Hash: Compile-Time Perfect Hash | PolyRnd | 64B_Line (64B) [Seq]`
|    12.1% |               25.03 |       39,954,711.33 |    0.2% |      2.85 | `10.2 Hash: Compile-Time Perfect Hash | PolyRnd | 64B_Line (64B) [Rnd]`
|    42.0% |                7.21 |      138,600,266.67 |    0.1% |      0.82 | `10.2 Hash: Compile-Time Perfect Hash | PolyRnd | 16B_Compact (8B) [Seq]`
|    27.7% |               10.92 |       91,567,492.40 |    0.7% |      1.24 | `10.2 Hash: Compile-Time Perfect Hash | PolyRnd | 16B_Compact (8B) [Rnd]`
|    35.4% |                8.56 |      116,789,836.69 |    0.1% |      0.98 | `10.2 Hash: Compile-Time Perfect Hash | PolyRnd | 60B_Split (60B) [Seq]`
|    12.4% |               24.43 |       40,932,050.07 |    0.4% |      2.79 | `10.2 Hash: Compile-Time Perfect Hash | PolyRnd | 60B_Split (60B) [Rnd]`
|    22.8% |               13.29 |       75,267,517.22 |    0.1% |      1.52 | `10.2 Hash: Compile-Time Perfect Hash | PolyRnd | 256B_Heavy (256B) [Seq]`
|    10.0% |               30.31 |       32,995,101.20 |    0.2% |      3.45 | `10.2 Hash: Compile-Time Perfect Hash | PolyRnd | 256B_Heavy (256B) [Rnd]`
|   103.5% |                2.93 |      341,484,051.75 |    1.1% |      0.34 | `11.1 Advanced: Flat LUT (8-bit, 256B) | Mono | 64B_Line (64B) [Seq]`
|    23.9% |               12.67 |       78,907,658.08 |    0.7% |      1.45 | `11.1 Advanced: Flat LUT (8-bit, 256B) | Mono | 64B_Line (64B) [Rnd]`
|   103.5% |                2.93 |      341,521,135.14 |    0.5% |      0.33 | `11.1 Advanced: Flat LUT (8-bit, 256B) | PolySorted | 64B_Line (64B) [Seq]`
|    23.8% |               12.74 |       78,511,350.89 |    0.7% |      1.44 | `11.1 Advanced: Flat LUT (8-bit, 256B) | PolySorted | 64B_Line (64B) [Rnd]`
|    36.4% |                8.32 |      120,241,019.59 |    0.3% |      0.95 | `11.1 Advanced: Flat LUT (8-bit, 256B) | PolyRnd | 64B_Line (64B) [Seq]`
|    14.3% |               21.23 |       47,100,105.39 |    0.3% |      2.42 | `11.1 Advanced: Flat LUT (8-bit, 256B) | PolyRnd | 64B_Line (64B) [Rnd]`
|    45.8% |                6.62 |      151,098,200.61 |    0.2% |      0.75 | `11.1 Advanced: Flat LUT (8-bit, 256B) | PolyRnd | 16B_Compact (8B) [Seq]`
|    28.3% |               10.69 |       93,519,241.27 |    0.2% |      1.22 | `11.1 Advanced: Flat LUT (8-bit, 256B) | PolyRnd | 16B_Compact (8B) [Rnd]`
|    37.5% |                8.08 |      123,836,844.23 |    0.2% |      0.92 | `11.1 Advanced: Flat LUT (8-bit, 256B) | PolyRnd | 60B_Split (60B) [Seq]`
|    14.7% |               20.58 |       48,580,061.94 |    0.2% |      2.35 | `11.1 Advanced: Flat LUT (8-bit, 256B) | PolyRnd | 60B_Split (60B) [Rnd]`
|    24.0% |               12.60 |       79,347,039.21 |    0.5% |      1.44 | `11.1 Advanced: Flat LUT (8-bit, 256B) | PolyRnd | 256B_Heavy (256B) [Seq]`
|    11.9% |               25.39 |       39,389,974.42 |    0.1% |      2.90 | `11.1 Advanced: Flat LUT (8-bit, 256B) | PolyRnd | 256B_Heavy (256B) [Rnd]`
|   103.9% |                2.92 |      343,024,792.62 |    0.1% |      0.34 | `11.2 Advanced: Flat LUT (16-bit, 64KB) | Mono | 64B_Line (64B) [Seq]`
|    24.0% |               12.63 |       79,203,490.10 |    0.8% |      1.44 | `11.2 Advanced: Flat LUT (16-bit, 64KB) | Mono | 64B_Line (64B) [Rnd]`
|   102.3% |                2.96 |      337,539,070.15 |    0.4% |      0.34 | `11.2 Advanced: Flat LUT (16-bit, 64KB) | PolySorted | 64B_Line (64B) [Seq]`
|    24.4% |               12.41 |       80,560,226.56 |    0.5% |      1.42 | `11.2 Advanced: Flat LUT (16-bit, 64KB) | PolySorted | 64B_Line (64B) [Rnd]`
|    36.9% |                8.21 |      121,770,444.85 |    0.2% |      0.94 | `11.2 Advanced: Flat LUT (16-bit, 64KB) | PolyRnd | 64B_Line (64B) [Seq]`
|    14.3% |               21.20 |       47,172,843.07 |    0.5% |      2.42 | `11.2 Advanced: Flat LUT (16-bit, 64KB) | PolyRnd | 64B_Line (64B) [Rnd]`
|    44.5% |                6.81 |      146,822,332.89 |    0.5% |      0.78 | `11.2 Advanced: Flat LUT (16-bit, 64KB) | PolyRnd | 16B_Compact (8B) [Seq]`
|    28.4% |               10.65 |       93,873,961.30 |    0.6% |      1.22 | `11.2 Advanced: Flat LUT (16-bit, 64KB) | PolyRnd | 16B_Compact (8B) [Rnd]`
|    37.0% |                8.18 |      122,218,311.24 |    0.5% |      0.93 | `11.2 Advanced: Flat LUT (16-bit, 64KB) | PolyRnd | 60B_Split (60B) [Seq]`
|    14.7% |               20.59 |       48,566,410.62 |    0.3% |      2.35 | `11.2 Advanced: Flat LUT (16-bit, 64KB) | PolyRnd | 60B_Split (60B) [Rnd]`
|    24.2% |               12.52 |       79,842,032.54 |    0.3% |      1.43 | `11.2 Advanced: Flat LUT (16-bit, 64KB) | PolyRnd | 256B_Heavy (256B) [Seq]`
|    11.8% |               25.57 |       39,108,411.65 |    0.2% |      2.91 | `11.2 Advanced: Flat LUT (16-bit, 64KB) | PolyRnd | 256B_Heavy (256B) [Rnd]`
|    98.5% |                3.08 |      324,931,815.09 |    1.0% |      0.35 | `11.3 Advanced: Hash (Linear Probe) | Mono | 64B_Line (64B) [Seq]`
|    18.0% |               16.84 |       59,381,166.59 |    0.7% |      1.92 | `11.3 Advanced: Hash (Linear Probe) | Mono | 64B_Line (64B) [Rnd]`
|    96.1% |                3.15 |      317,124,735.73 |    0.9% |      0.36 | `11.3 Advanced: Hash (Linear Probe) | PolySorted | 64B_Line (64B) [Seq]`
|    19.2% |               15.78 |       63,376,657.62 |    0.6% |      1.80 | `11.3 Advanced: Hash (Linear Probe) | PolySorted | 64B_Line (64B) [Rnd]`
|    32.0% |                9.48 |      105,493,392.60 |    0.2% |      1.08 | `11.3 Advanced: Hash (Linear Probe) | PolyRnd | 64B_Line (64B) [Seq]`
|    11.6% |               26.22 |       38,137,574.44 |    0.3% |      2.99 | `11.3 Advanced: Hash (Linear Probe) | PolyRnd | 64B_Line (64B) [Rnd]`
|    37.0% |                8.18 |      122,220,402.50 |    0.2% |      0.93 | `11.3 Advanced: Hash (Linear Probe) | PolyRnd | 16B_Compact (8B) [Seq]`
|    24.8% |               12.20 |       81,988,876.52 |    1.1% |      1.39 | `11.3 Advanced: Hash (Linear Probe) | PolyRnd | 16B_Compact (8B) [Rnd]`
|    32.3% |                9.38 |      106,635,742.30 |    0.2% |      1.07 | `11.3 Advanced: Hash (Linear Probe) | PolyRnd | 60B_Split (60B) [Seq]`
|    12.2% |               24.92 |       40,129,085.23 |    0.4% |      2.84 | `11.3 Advanced: Hash (Linear Probe) | PolyRnd | 60B_Split (60B) [Rnd]`
|    21.2% |               14.28 |       70,011,556.28 |    0.1% |      1.63 | `11.3 Advanced: Hash (Linear Probe) | PolyRnd | 256B_Heavy (256B) [Seq]`
|     9.9% |               30.65 |       32,627,212.48 |    0.2% |      3.49 | `11.3 Advanced: Hash (Linear Probe) | PolyRnd | 256B_Heavy (256B) [Rnd]`
|    96.4% |                3.14 |      318,150,088.24 |    1.1% |      0.36 | `11.4 Advanced: AVX2 SIMD Search | Mono | 64B_Line (64B) [Seq]`
|    17.7% |               17.11 |       58,447,483.56 |    0.7% |      1.95 | `11.4 Advanced: AVX2 SIMD Search | Mono | 64B_Line (64B) [Rnd]`
|    93.3% |                3.25 |      307,988,868.92 |    0.6% |      0.37 | `11.4 Advanced: AVX2 SIMD Search | PolySorted | 64B_Line (64B) [Seq]`
|    16.6% |               18.29 |       54,678,572.01 |    0.4% |      2.09 | `11.4 Advanced: AVX2 SIMD Search | PolySorted | 64B_Line (64B) [Rnd]`
|    23.7% |               12.81 |       78,079,402.85 |    0.1% |      1.46 | `11.4 Advanced: AVX2 SIMD Search | PolyRnd | 64B_Line (64B) [Seq]`
|     9.8% |               30.94 |       32,316,854.21 |    0.2% |      3.53 | `11.4 Advanced: AVX2 SIMD Search | PolyRnd | 64B_Line (64B) [Rnd]`
|    25.8% |               11.74 |       85,206,199.00 |    0.4% |      1.34 | `11.4 Advanced: AVX2 SIMD Search | PolyRnd | 16B_Compact (8B) [Seq]`
|    19.5% |               15.54 |       64,358,858.94 |    0.5% |      1.77 | `11.4 Advanced: AVX2 SIMD Search | PolyRnd | 16B_Compact (8B) [Rnd]`
|    23.7% |               12.81 |       78,080,900.08 |    0.1% |      1.46 | `11.4 Advanced: AVX2 SIMD Search | PolyRnd | 60B_Split (60B) [Seq]`
|    10.5% |               28.86 |       34,650,875.11 |    0.2% |      3.29 | `11.4 Advanced: AVX2 SIMD Search | PolyRnd | 60B_Split (60B) [Rnd]`
|    16.7% |               18.15 |       55,081,415.50 |    0.3% |      2.07 | `11.4 Advanced: AVX2 SIMD Search | PolyRnd | 256B_Heavy (256B) [Seq]`
|     8.4% |               36.16 |       27,652,802.47 |    0.1% |      4.12 | `11.4 Advanced: AVX2 SIMD Search | PolyRnd | 256B_Heavy (256B) [Rnd]`
|    73.5% |                4.12 |      242,531,642.29 |    0.5% |      0.47 | `11.5 Advanced: Branchless BinSearch | Mono | 64B_Line (64B) [Seq]`
|    11.2% |               27.04 |       36,979,222.76 |    0.7% |      3.08 | `11.5 Advanced: Branchless BinSearch | Mono | 64B_Line (64B) [Rnd]`
|    72.1% |                4.20 |      237,951,829.63 |    0.6% |      0.48 | `11.5 Advanced: Branchless BinSearch | PolySorted | 64B_Line (64B) [Seq]`
|    11.9% |               25.38 |       39,405,088.25 |    0.5% |      2.88 | `11.5 Advanced: Branchless BinSearch | PolySorted | 64B_Line (64B) [Rnd]`
|    21.1% |               14.39 |       69,515,720.78 |    0.2% |      1.64 | `11.5 Advanced: Branchless BinSearch | PolyRnd | 64B_Line (64B) [Seq]`
|     8.1% |               37.24 |       26,849,640.40 |    0.8% |      4.26 | `11.5 Advanced: Branchless BinSearch | PolyRnd | 64B_Line (64B) [Rnd]`
|    22.8% |               13.28 |       75,305,032.45 |    0.1% |      1.51 | `11.5 Advanced: Branchless BinSearch | PolyRnd | 16B_Compact (8B) [Seq]`
|    19.1% |               15.85 |       63,109,126.33 |    0.7% |      1.81 | `11.5 Advanced: Branchless BinSearch | PolyRnd | 16B_Compact (8B) [Rnd]`
|    21.6% |               14.01 |       71,393,328.06 |    0.2% |      1.60 | `11.5 Advanced: Branchless BinSearch | PolyRnd | 60B_Split (60B) [Seq]`
|     8.4% |               36.18 |       27,640,226.70 |    0.2% |      4.15 | `11.5 Advanced: Branchless BinSearch | PolyRnd | 60B_Split (60B) [Rnd]`
|    16.3% |               18.54 |       53,946,316.94 |    0.0% |      2.12 | `11.5 Advanced: Branchless BinSearch | PolyRnd | 256B_Heavy (256B) [Seq]`
|     6.8% |               44.35 |       22,546,094.36 |    0.3% |      5.05 | `11.5 Advanced: Branchless BinSearch | PolyRnd | 256B_Heavy (256B) [Rnd]`
|    66.7% |                4.54 |      220,275,840.42 |    0.3% |      0.52 | `11.6 Advanced: Eytzinger BFS Search | Mono | 64B_Line (64B) [Seq]`
|     8.4% |               35.92 |       27,841,460.28 |    1.0% |      4.11 | `11.6 Advanced: Eytzinger BFS Search | Mono | 64B_Line (64B) [Rnd]`
|    71.2% |                4.26 |      234,842,736.09 |    0.3% |      0.49 | `11.6 Advanced: Eytzinger BFS Search | PolySorted | 64B_Line (64B) [Seq]`
|    10.1% |               30.04 |       33,286,060.96 |    0.8% |      3.44 | `11.6 Advanced: Eytzinger BFS Search | PolySorted | 64B_Line (64B) [Rnd]`
|    20.6% |               14.71 |       67,991,657.88 |    0.2% |      1.68 | `11.6 Advanced: Eytzinger BFS Search | PolyRnd | 64B_Line (64B) [Seq]`
|     7.4% |               41.02 |       24,380,890.32 |    0.2% |      4.68 | `11.6 Advanced: Eytzinger BFS Search | PolyRnd | 64B_Line (64B) [Rnd]`
|    21.6% |               14.06 |       71,125,407.84 |    0.2% |      1.60 | `11.6 Advanced: Eytzinger BFS Search | PolyRnd | 16B_Compact (8B) [Seq]`
|    19.3% |               15.70 |       63,683,816.59 |    0.2% |      1.79 | `11.6 Advanced: Eytzinger BFS Search | PolyRnd | 16B_Compact (8B) [Rnd]`
|    21.0% |               14.41 |       69,401,670.85 |    0.1% |      1.64 | `11.6 Advanced: Eytzinger BFS Search | PolyRnd | 60B_Split (60B) [Seq]`
|     7.6% |               39.63 |       25,231,766.39 |    0.7% |      4.52 | `11.6 Advanced: Eytzinger BFS Search | PolyRnd | 60B_Split (60B) [Rnd]`
|    16.1% |               18.81 |       53,176,639.50 |    0.1% |      2.14 | `11.6 Advanced: Eytzinger BFS Search | PolyRnd | 256B_Heavy (256B) [Seq]`
|     6.4% |               47.68 |       20,974,039.32 |    0.2% |      5.44 | `11.6 Advanced: Eytzinger BFS Search | PolyRnd | 256B_Heavy (256B) [Rnd]`
|   105.6% |                2.87 |      348,385,776.28 |    0.3% |      0.33 | `12.1 Table: Direct FnPtr Array (No Switch) | Mono | 64B_Line (64B) [Seq]`
|    24.0% |               12.63 |       79,179,071.39 |    1.1% |      1.44 | `12.1 Table: Direct FnPtr Array (No Switch) | Mono | 64B_Line (64B) [Rnd]`
|   105.2% |                2.88 |      347,136,241.72 |    0.6% |      0.33 | `12.1 Table: Direct FnPtr Array (No Switch) | PolySorted | 64B_Line (64B) [Seq]`
|    24.9% |               12.19 |       82,039,793.68 |    0.4% |      1.39 | `12.1 Table: Direct FnPtr Array (No Switch) | PolySorted | 64B_Line (64B) [Rnd]`
|    39.6% |                7.66 |      130,567,754.68 |    0.7% |      0.87 | `12.1 Table: Direct FnPtr Array (No Switch) | PolyRnd | 64B_Line (64B) [Seq]`
|    15.2% |               19.96 |       50,100,769.35 |    0.2% |      2.27 | `12.1 Table: Direct FnPtr Array (No Switch) | PolyRnd | 64B_Line (64B) [Rnd]`
|    52.3% |                5.79 |      172,714,223.21 |    0.3% |      0.66 | `12.1 Table: Direct FnPtr Array (No Switch) | PolyRnd | 16B_Compact (8B) [Seq]`
|    29.2% |               10.39 |       96,265,520.69 |    0.2% |      1.18 | `12.1 Table: Direct FnPtr Array (No Switch) | PolyRnd | 16B_Compact (8B) [Rnd]`
|    41.8% |                7.24 |      138,083,783.72 |    0.7% |      0.83 | `12.1 Table: Direct FnPtr Array (No Switch) | PolyRnd | 60B_Split (60B) [Seq]`
|    15.4% |               19.61 |       50,990,505.57 |    1.2% |      2.23 | `12.1 Table: Direct FnPtr Array (No Switch) | PolyRnd | 60B_Split (60B) [Rnd]`
|    24.1% |               12.58 |       79,506,887.68 |    0.2% |      1.43 | `12.1 Table: Direct FnPtr Array (No Switch) | PolyRnd | 256B_Heavy (256B) [Seq]`
|    12.8% |               23.63 |       42,325,407.69 |    0.2% |      2.69 | `12.1 Table: Direct FnPtr Array (No Switch) | PolyRnd | 256B_Heavy (256B) [Rnd]`
|    31.7% |                9.55 |      104,733,975.70 |    0.4% |      1.09 | `12.2 Pointers: 64-bit Tagged Pointer (48b Addr + 16b Tag) | Mono | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    17.5% |               17.30 |       57,799,223.18 |    0.3% |      1.98 | `12.2 Pointers: 64-bit Tagged Pointer (48b Addr + 16b Tag) | Mono | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    31.2% |                9.71 |      102,963,424.65 |    0.5% |      1.11 | `12.2 Pointers: 64-bit Tagged Pointer (48b Addr + 16b Tag) | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    19.5% |               15.56 |       64,250,560.05 |    1.3% |      1.78 | `12.2 Pointers: 64-bit Tagged Pointer (48b Addr + 16b Tag) | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    28.2% |               10.75 |       93,020,371.46 |    0.2% |      1.23 | `12.2 Pointers: 64-bit Tagged Pointer (48b Addr + 16b Tag) | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    15.5% |               19.49 |       51,298,151.01 |    0.7% |      2.23 | `12.2 Pointers: 64-bit Tagged Pointer (48b Addr + 16b Tag) | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    31.8% |                9.53 |      104,962,374.08 |    0.1% |      1.09 | `12.2 Pointers: 64-bit Tagged Pointer (48b Addr + 16b Tag) | PolyRnd | HeapCompact | 64B_Line (64B) [Seq]`
|    15.6% |               19.44 |       51,428,618.45 |    0.3% |      2.22 | `12.2 Pointers: 64-bit Tagged Pointer (48b Addr + 16b Tag) | PolyRnd | HeapCompact | 64B_Line (64B) [Rnd]`
|    32.1% |                9.45 |      105,836,246.42 |    0.2% |      1.08 | `12.2 Pointers: 64-bit Tagged Pointer (48b Addr + 16b Tag) | PolyRnd | HeapJitter | 64B_Line (64B) [Seq]`
|    15.5% |               19.56 |       51,120,458.20 |    0.2% |      2.23 | `12.2 Pointers: 64-bit Tagged Pointer (48b Addr + 16b Tag) | PolyRnd | HeapJitter | 64B_Line (64B) [Rnd]`
|    47.6% |                6.37 |      157,096,850.21 |    0.3% |      0.73 | `12.2 Pointers: 64-bit Tagged Pointer (48b Addr + 16b Tag) | PolyRnd | HeapTrash1to1 | 16B_Compact (8B) [Seq]`
|    18.1% |               16.75 |       59,701,869.93 |    0.9% |      1.91 | `12.2 Pointers: 64-bit Tagged Pointer (48b Addr + 16b Tag) | PolyRnd | HeapTrash1to1 | 16B_Compact (8B) [Rnd]`
|    31.6% |                9.57 |      104,458,279.36 |    0.6% |      1.09 | `12.2 Pointers: 64-bit Tagged Pointer (48b Addr + 16b Tag) | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Seq]`
|    15.6% |               19.36 |       51,639,655.90 |    0.3% |      2.21 | `12.2 Pointers: 64-bit Tagged Pointer (48b Addr + 16b Tag) | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Rnd]`
|    27.0% |               11.23 |       89,024,029.56 |    0.4% |      1.28 | `12.2 Pointers: 64-bit Tagged Pointer (48b Addr + 16b Tag) | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Seq]`
|    15.0% |               20.24 |       49,398,523.58 |    1.0% |      2.31 | `12.2 Pointers: 64-bit Tagged Pointer (48b Addr + 16b Tag) | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Rnd]`
|    34.5% |                8.77 |      113,989,731.80 |    0.6% |      1.00 | `13.1 PIC: Speculative Bimorphic Inline Cache | Mono | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    12.0% |               25.18 |       39,715,772.75 |    0.9% |      2.88 | `13.1 PIC: Speculative Bimorphic Inline Cache | Mono | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    33.4% |                9.06 |      110,326,638.24 |    0.4% |      1.03 | `13.1 PIC: Speculative Bimorphic Inline Cache | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    12.8% |               23.66 |       42,273,824.47 |    0.5% |      2.70 | `13.1 PIC: Speculative Bimorphic Inline Cache | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    20.1% |               15.08 |       66,334,194.16 |    0.3% |      1.72 | `13.1 PIC: Speculative Bimorphic Inline Cache | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|     8.6% |               35.23 |       28,384,458.79 |    0.5% |      4.02 | `13.1 PIC: Speculative Bimorphic Inline Cache | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    24.4% |               12.41 |       80,593,771.93 |    0.7% |      1.41 | `13.1 PIC: Speculative Bimorphic Inline Cache | PolyRnd | HeapCompact | 64B_Line (64B) [Seq]`
|     8.7% |               34.71 |       28,813,932.11 |    0.7% |      3.96 | `13.1 PIC: Speculative Bimorphic Inline Cache | PolyRnd | HeapCompact | 64B_Line (64B) [Rnd]`
|    24.1% |               12.56 |       79,586,954.32 |    0.2% |      1.43 | `13.1 PIC: Speculative Bimorphic Inline Cache | PolyRnd | HeapJitter | 64B_Line (64B) [Seq]`
|     8.7% |               35.00 |       28,569,243.86 |    0.2% |      3.98 | `13.1 PIC: Speculative Bimorphic Inline Cache | PolyRnd | HeapJitter | 64B_Line (64B) [Rnd]`
|    31.8% |                9.54 |      104,793,975.05 |    0.5% |      1.09 | `13.1 PIC: Speculative Bimorphic Inline Cache | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Seq]`
|     9.1% |               33.17 |       30,150,589.78 |    0.5% |      3.78 | `13.1 PIC: Speculative Bimorphic Inline Cache | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Rnd]`
|    23.2% |               13.08 |       76,428,470.59 |    0.3% |      1.50 | `13.1 PIC: Speculative Bimorphic Inline Cache | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Seq]`
|     8.7% |               34.79 |       28,746,502.02 |    0.3% |      3.96 | `13.1 PIC: Speculative Bimorphic Inline Cache | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Rnd]`
|    18.1% |               16.71 |       59,857,519.15 |    0.3% |      1.91 | `13.1 PIC: Speculative Bimorphic Inline Cache | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Seq]`
|     8.4% |               36.00 |       27,777,859.23 |    0.2% |      4.11 | `13.1 PIC: Speculative Bimorphic Inline Cache | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Rnd]`
|    32.2% |                9.41 |      106,245,156.71 |    0.7% |      1.08 | `13.2 RTTI: dynamic_cast Cascade | Mono | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|     5.9% |               51.00 |       19,608,712.07 |    0.5% |      5.81 | `13.2 RTTI: dynamic_cast Cascade | Mono | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|     2.4% |              125.60 |        7,961,922.53 |    0.1% |     14.31 | `13.2 RTTI: dynamic_cast Cascade | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|     1.4% |              211.66 |        4,724,547.65 |    0.1% |     24.11 | `13.2 RTTI: dynamic_cast Cascade | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|     2.1% |              147.39 |        6,784,544.05 |    0.1% |     16.79 | `13.2 RTTI: dynamic_cast Cascade | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|     1.2% |              254.97 |        3,922,043.80 |    0.3% |     29.09 | `13.2 RTTI: dynamic_cast Cascade | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|     2.4% |              127.37 |        7,851,121.31 |    0.1% |     14.53 | `13.2 RTTI: dynamic_cast Cascade | PolyRnd | HeapCompact | 64B_Line (64B) [Seq]`
|     1.2% |              257.03 |        3,890,592.74 |    2.3% |     29.77 | `13.2 RTTI: dynamic_cast Cascade | PolyRnd | HeapCompact | 64B_Line (64B) [Rnd]`
|     2.4% |              127.81 |        7,824,348.08 |    0.1% |     14.56 | `13.2 RTTI: dynamic_cast Cascade | PolyRnd | HeapJitter | 64B_Line (64B) [Seq]`
|     1.1% |              265.25 |        3,769,975.12 |    2.1% |     30.49 | `13.2 RTTI: dynamic_cast Cascade | PolyRnd | HeapJitter | 64B_Line (64B) [Rnd]`
|     2.6% |              115.36 |        8,668,869.55 |    0.1% |     13.14 | `13.2 RTTI: dynamic_cast Cascade | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Seq]`
|     1.2% |              249.99 |        4,000,233.31 |    2.2% |     28.56 | `13.2 RTTI: dynamic_cast Cascade | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Rnd]`
|     2.2% |              134.88 |        7,413,951.82 |    0.1% |     15.38 | `13.2 RTTI: dynamic_cast Cascade | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Seq]`
|     1.2% |              253.42 |        3,945,941.74 |    0.3% |     28.90 | `13.2 RTTI: dynamic_cast Cascade | PolyRnd | HeapTrash1to1 | 60B_Split (64B) [Rnd]`
|     2.1% |              145.58 |        6,868,972.14 |    0.1% |     16.59 | `13.2 RTTI: dynamic_cast Cascade | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Seq]`
|     1.1% |              267.12 |        3,743,705.58 |    0.6% |     30.29 | `13.2 RTTI: dynamic_cast Cascade | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Rnd]`
|   101.7% |                2.98 |      335,653,289.90 |    1.6% |      0.34 | `13.3 RTTI: std::any (In-Place SBO) | Mono | 64B_Line (64B) [Seq]`
|    20.0% |               15.12 |       66,138,936.74 |    0.3% |      1.73 | `13.3 RTTI: std::any (In-Place SBO) | Mono | 64B_Line (64B) [Rnd]`
|     6.5% |               46.54 |       21,488,644.98 |    0.3% |      5.31 | `13.3 RTTI: std::any (In-Place SBO) | PolySorted | 64B_Line (64B) [Seq]`
|     3.1% |               97.22 |       10,286,448.00 |    0.1% |     11.09 | `13.3 RTTI: std::any (In-Place SBO) | PolySorted | 64B_Line (64B) [Rnd]`
|     5.5% |               55.34 |       18,069,589.60 |    0.1% |      6.31 | `13.3 RTTI: std::any (In-Place SBO) | PolyRnd | 64B_Line (64B) [Seq]`
|     2.1% |              142.53 |        7,016,090.75 |    0.2% |     16.26 | `13.3 RTTI: std::any (In-Place SBO) | PolyRnd | 64B_Line (64B) [Rnd]`
|     5.5% |               55.20 |       18,117,554.67 |    0.1% |      6.29 | `13.3 RTTI: std::any (In-Place SBO) | PolyRnd | 16B_Compact (64B) [Seq]`
|     2.1% |              142.27 |        7,029,067.52 |    0.2% |     16.23 | `13.3 RTTI: std::any (In-Place SBO) | PolyRnd | 16B_Compact (64B) [Rnd]`
|     5.5% |               55.28 |       18,088,985.51 |    0.3% |      6.31 | `13.3 RTTI: std::any (In-Place SBO) | PolyRnd | 60B_Split (64B) [Seq]`
|     2.1% |              141.95 |        7,044,555.70 |    0.2% |     16.17 | `13.3 RTTI: std::any (In-Place SBO) | PolyRnd | 60B_Split (64B) [Rnd]`
|     5.5% |               55.20 |       18,115,705.01 |    0.2% |      6.30 | `13.3 RTTI: std::any (In-Place SBO) | PolyRnd | 256B_Heavy (64B) [Seq]`
|     2.1% |              142.67 |        7,008,976.35 |    0.2% |     16.26 | `13.3 RTTI: std::any (In-Place SBO) | PolyRnd | 256B_Heavy (64B) [Rnd]`
|    50.1% |                6.04 |      165,436,113.93 |    0.5% |      0.69 | `13.4 RTTI: std::any (Payload-Scaled) | Mono | 64B_Line (64B) [Seq]`
|     9.8% |               30.85 |       32,411,702.96 |    1.3% |      3.53 | `13.4 RTTI: std::any (Payload-Scaled) | Mono | 64B_Line (64B) [Rnd]`
|     5.6% |               54.06 |       18,497,204.87 |    0.5% |      6.17 | `13.4 RTTI: std::any (Payload-Scaled) | PolySorted | 64B_Line (64B) [Seq]`
|     2.1% |              143.60 |        6,963,905.83 |    0.2% |     16.36 | `13.4 RTTI: std::any (Payload-Scaled) | PolySorted | 64B_Line (64B) [Rnd]`
|     4.9% |               62.23 |       16,069,904.80 |    0.2% |      7.09 | `13.4 RTTI: std::any (Payload-Scaled) | PolyRnd | 64B_Line (64B) [Seq]`
|     1.8% |              166.10 |        6,020,296.07 |    0.4% |     18.92 | `13.4 RTTI: std::any (Payload-Scaled) | PolyRnd | 64B_Line (64B) [Rnd]`
|     5.4% |               56.52 |       17,692,053.88 |    0.2% |      6.44 | `13.4 RTTI: std::any (Payload-Scaled) | PolyRnd | 16B_Compact (64B) [Seq]`
|     2.0% |              149.35 |        6,695,634.49 |    0.8% |     17.05 | `13.4 RTTI: std::any (Payload-Scaled) | PolyRnd | 16B_Compact (64B) [Rnd]`
|     4.8% |               62.72 |       15,943,620.17 |    0.1% |      7.16 | `13.4 RTTI: std::any (Payload-Scaled) | PolyRnd | 60B_Split (64B) [Seq]`
|     1.8% |              166.27 |        6,014,194.22 |    0.1% |     18.96 | `13.4 RTTI: std::any (Payload-Scaled) | PolyRnd | 60B_Split (64B) [Rnd]`
|     4.1% |               73.73 |       13,563,267.49 |    0.3% |      8.41 | `13.4 RTTI: std::any (Payload-Scaled) | PolyRnd | 256B_Heavy (64B) [Seq]`
|     1.8% |              166.30 |        6,013,221.63 |    0.1% |     18.96 | `13.4 RTTI: std::any (Payload-Scaled) | PolyRnd | 256B_Heavy (64B) [Rnd]`
|    17.9% |               16.89 |       59,202,635.23 |    0.2% |      1.93 | `14.1 C++20 Coroutine: coroutine_handle::resume() | Mono | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    10.0% |               30.29 |       33,009,016.08 |    0.5% |      3.45 | `14.1 C++20 Coroutine: coroutine_handle::resume() | Mono | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    17.6% |               17.18 |       58,196,784.28 |    0.2% |      1.96 | `14.1 C++20 Coroutine: coroutine_handle::resume() | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|    10.7% |               28.37 |       35,250,786.83 |    0.6% |      3.23 | `14.1 C++20 Coroutine: coroutine_handle::resume() | PolySorted | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    14.7% |               20.61 |       48,522,137.01 |    0.6% |      2.35 | `14.1 C++20 Coroutine: coroutine_handle::resume() | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Seq]`
|     7.2% |               41.99 |       23,816,201.69 |    0.3% |      4.80 | `14.1 C++20 Coroutine: coroutine_handle::resume() | PolyRnd | HeapTrash1to1 | 64B_Line (64B) [Rnd]`
|    16.3% |               18.57 |       53,858,591.04 |    0.1% |      2.13 | `14.1 C++20 Coroutine: coroutine_handle::resume() | PolyRnd | HeapCompact | 64B_Line (64B) [Seq]`
|     7.3% |               41.57 |       24,054,893.83 |    0.3% |      4.74 | `14.1 C++20 Coroutine: coroutine_handle::resume() | PolyRnd | HeapCompact | 64B_Line (64B) [Rnd]`
|    16.2% |               18.74 |       53,368,893.62 |    0.1% |      2.13 | `14.1 C++20 Coroutine: coroutine_handle::resume() | PolyRnd | HeapJitter | 64B_Line (64B) [Seq]`
|     7.3% |               41.52 |       24,085,380.26 |    0.2% |      4.74 | `14.1 C++20 Coroutine: coroutine_handle::resume() | PolyRnd | HeapJitter | 64B_Line (64B) [Rnd]`
|    18.5% |               16.42 |       60,914,056.02 |    0.1% |      1.87 | `14.1 C++20 Coroutine: coroutine_handle::resume() | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Seq]`
|     8.1% |               37.32 |       26,796,447.22 |    0.2% |      4.27 | `14.1 C++20 Coroutine: coroutine_handle::resume() | PolyRnd | HeapTrash1to1 | 16B_Compact (16B) [Rnd]`
|    16.5% |               18.35 |       54,499,383.99 |    0.2% |      2.09 | `14.1 C++20 Coroutine: coroutine_handle::resume() | PolyRnd | HeapTrash1to1 | 60B_Split (40B) [Seq]`
|     7.7% |               39.38 |       25,395,688.64 |    0.2% |      4.50 | `14.1 C++20 Coroutine: coroutine_handle::resume() | PolyRnd | HeapTrash1to1 | 60B_Split (40B) [Rnd]`
|    12.6% |               24.05 |       41,587,589.09 |    0.1% |      2.74 | `14.1 C++20 Coroutine: coroutine_handle::resume() | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Seq]`
|     7.0% |               43.03 |       23,240,829.02 |    0.5% |      4.90 | `14.1 C++20 Coroutine: coroutine_handle::resume() | PolyRnd | HeapTrash1to1 | 256B_Heavy (256B) [Rnd]`
|   103.2% |                2.94 |      340,546,615.16 |    0.8% |      0.33 | `15.1 Data-Driven: Branchless Parameter LUT | Mono | 64B_Line (64B) [Seq]`
|    21.1% |               14.35 |       69,666,840.11 |    0.4% |      1.64 | `15.1 Data-Driven: Branchless Parameter LUT | Mono | 64B_Line (64B) [Rnd]`
|   102.7% |                2.95 |      338,955,339.64 |    0.3% |      0.34 | `15.1 Data-Driven: Branchless Parameter LUT | PolySorted | 64B_Line (64B) [Seq]`
|    23.4% |               12.95 |       77,194,795.62 |    0.8% |      1.48 | `15.1 Data-Driven: Branchless Parameter LUT | PolySorted | 64B_Line (64B) [Rnd]`
|   102.2% |                2.96 |      337,285,191.49 |    0.4% |      0.34 | `15.1 Data-Driven: Branchless Parameter LUT | PolyRnd | 64B_Line (64B) [Seq]`
|    20.8% |               14.58 |       68,593,515.68 |    0.3% |      1.66 | `15.1 Data-Driven: Branchless Parameter LUT | PolyRnd | 64B_Line (64B) [Rnd]`
|   292.4% |                1.04 |      965,108,489.55 |    0.1% |      0.12 | `15.1 Data-Driven: Branchless Parameter LUT | PolyRnd | 16B_Compact (8B) [Seq]`
|   109.3% |                2.77 |      360,847,992.78 |    1.1% |      0.31 | `15.1 Data-Driven: Branchless Parameter LUT | PolyRnd | 16B_Compact (8B) [Rnd]`
|   108.1% |                2.80 |      356,770,346.93 |    0.5% |      0.32 | `15.1 Data-Driven: Branchless Parameter LUT | PolyRnd | 60B_Split (60B) [Seq]`
|    21.3% |               14.22 |       70,310,725.07 |    0.5% |      1.62 | `15.1 Data-Driven: Branchless Parameter LUT | PolyRnd | 60B_Split (60B) [Rnd]`
|    41.8% |                7.25 |      137,904,523.53 |    0.5% |      0.83 | `15.1 Data-Driven: Branchless Parameter LUT | PolyRnd | 256B_Heavy (256B) [Seq]`
|    17.4% |               17.46 |       57,280,812.44 |    0.6% |      1.99 | `15.1 Data-Driven: Branchless Parameter LUT | PolyRnd | 256B_Heavy (256B) [Rnd]`
|   106.2% |                2.85 |      350,488,725.60 |    1.2% |      0.33 | `35 ECS: Archetype Buckets (AoS) | 64B_Line (64B) [Seq]`
|   379.8% |                0.80 |    1,253,641,089.93 |    0.1% |      0.09 | `35 ECS: Archetype Buckets (AoS) | 16B_Compact (4B) [Seq]`
|   113.1% |                2.68 |      373,441,755.92 |    1.0% |      0.31 | `35 ECS: Archetype Buckets (AoS) | 60B_Split (60B) [Seq]`
|    43.2% |                7.02 |      142,415,535.02 |    0.2% |      0.80 | `35 ECS: Archetype Buckets (AoS) | 256B_Heavy (256B) [Seq]`
|   409.3% |                0.74 |    1,350,771,528.91 |    0.3% |      0.08 | `15.0 ECS: SoA Hot/Cold Split (4B Hot Stream) | 64B_Line (64B Total) [Seq]`
|   407.2% |                0.74 |    1,344,054,141.66 |    0.3% |      0.08 | `15.0 ECS: SoA Hot/Cold Split (4B Hot Stream) | 16B_Compact (4B Total) [Seq]`
|   409.0% |                0.74 |    1,349,983,125.21 |    0.3% |      0.08 | `15.0 ECS: SoA Hot/Cold Split (4B Hot Stream) | 60B_Split (60B Total) [Seq]`
|   407.6% |                0.74 |    1,345,170,836.70 |    0.1% |      0.08 | `15.0 ECS: SoA Hot/Cold Split (4B Hot Stream) | 256B_Heavy (256B Total) [Seq]`
[Cleaning up...]