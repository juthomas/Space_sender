# Clone with submodules

`git clone --recurse-submodules https://github.com/juthomas/Space_sender.git`


# Build

`cd Space_sender` <br/>
`make`


# Launch

`./data_sender` <br/>
or <br/>
`./data_sender [path to data files] [path to midi files]` 

# Modification of the tester configuration

in <br/>
`inc/sender.h` <br/>
change <br/>
`[13] # define SAMPLES_NU 10 //NUMBER OF SAMPLES IN FILES` <br/>
`[14] # define SAMPLE_RATE 1 //RATE LOOP IN SECONDS` <br/>
`[15] # define FILES_NU 10 //NUMBER OF FILES` 

by default it's a 100 seconds test (10 * 10 * 1)

# Update git submodule
`git submodule update --remote Space_MIDI`