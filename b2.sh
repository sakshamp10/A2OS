rm -r -f kernel2
mkdir /home/saksham/kernel2
cp /home/saksham/linux-5.19.9.tar.xz /home/saksham/kernel2/linux-5.19.9.tar.xz
cd /home/saksham/kernel2
tar -xvf linux-5.19.9.tar.xz
cd linux-5.19.9
make mrproper
cp /home/saksham/config/.config /home/saksham/kernel2/linux-5.19.9
make -j$(nproc)
