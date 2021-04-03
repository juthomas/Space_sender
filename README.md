# Clone with submodules

`git clone --recurse-submodules https://github.com/juthomas/Space_sender.git`

<br/>

# Build

`cd Space_sender` 
`make`

<br/>

# Launch

`./data_sender` 
or 
`./data_sender [path to data files] [path to midi files]` 

# modification of the tester configuration

in 
`inc/sender.h` 
change 
`[13] # define SAMPLES_NU 10 //NUMBER OF SAMPLES IN FILES` 
`[14] # define SAMPLE_RATE 1 //RATE LOOP IN SECONDS` 
`[15] # define FILES_NU 10 //NUMBER OF FILES` 