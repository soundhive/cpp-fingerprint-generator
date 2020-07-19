# cpp_fingerprint_generator

Library that simplify creation of fingerprints from an audio file.

Give a `mp3` or `wav` file as input, get fingerprints as hash and offset pairs as output in a txt file.

This piece of software relies on [my own wav file decoder](https://github.com/soundhive/cpp-canonical-wav-decoder) to read wav files, [minimp3](https://github.com/lieff/minimp3) to read mp3 files, and the CPP port of [DejaVu](https://github.com/salsowelim/dejavu_cpp_port) to generate the hashes.

When you run it, it will create a `TEMP` directory in which it will dump the PCM files it requires to then generate the fingerprints (I intend to mmake this lib able to run without having to dump a file). 

As an output, you will get at the specified output directory a text file containing the prints.

## Compile

```bash
git clone --recurse-submodules https://github.com/soundhive/cpp-fingerprint-generator/tree/master
cd cpp-fingerprint-generator
mkdir build
cd build
cmake ..
cmake--build . 
```
## Use

```bash
chmod +x cpp_fingerprint_generator
./cpp_fingerprint_generator path/to/input.wav path/to/output_prints.txt
```
