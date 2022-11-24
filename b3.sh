rm -r -f kernel3
mkdir /home/saksham/kernel3
cp /home/saksham/linux-5.19.9.tar.xz /home/saksham/kernel3/linux-5.19.9.tar.xz
cd /home/saksham/kernel3
tar -xvf linux-5.19.9.tar.xz
cd linux-5.19.9
make mrproper
cp /home/saksham/config/.config /home/saksham/kernel3/linux-5.19.9
make -j$(nproc)
