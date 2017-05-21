# Introduction
The latest video coding standard High Efficiency Video Coding (HEVC) has made a significant progress in compression efficiency than previous standard H.264/Advanced Video Coding (AVC) while it has led to a tremendous increase in encoding computations as well. Recently, a Bayesian Model based Transform Unit (TU) depth decision approach has been proved to accelerate TU depth decision efficiently. Nevertheless, numerous variance computations limits its practical applications, In this work, we propose a novel relevant feature as reference based on Bayesian model for fast TU depth decision and evaluate their performances. Experimental results demonstrate that the best performance is achieved while the depths of upper TU, left TU and co-located TU are all taken into considerations. Moreover, compared with previous research, the proposed algorithm reduces much more encoding computations while maintaining almost the same video quality and compression efficiency.

# Installation
In mac/linux,
```
cd build/linux
make release
```
Then the execution files will be generated in ```bin/```

# Execution
The configuration information is defined in configuration files, which are in ```cfg/```. To use HEVC, the command is like
```
cd bin/
./TAppEncoderStatic -c ../cfg/encoder_randomaccess_main.cfg -c ../cfg/per-sequence/RaceHorses.cfg
```
