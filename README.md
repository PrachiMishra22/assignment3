# assignment3
My code is working fine for small text .
I have added that code with Text= "ABRACADABRA".But when i am reading whole DNA sequence , it is performing calculations for only first 16 sequences. I could not figure out why.So i have added both the codes.
Also, I could not properly use cmake so I had copied my code in the file (libdivsufsort/build/examples/ds202_sample1) 
COMMANDS to EXECUTE
Copy the code and paste it in (libdivsufsort/build/examples/ds202_sample1)
git clone https://github.com/cjain7/libdivsufsort.git
cd libdivsufsort
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE="Release" -DCMAKE_INSTALL_PREFIX=$PWD ..
make
./ds202_sample1

