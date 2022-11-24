rm -r -f kernel1
mkdir /home/saksham/kernel1
cp /home/saksham/linux-5.19.9.tar.xz /home/saksham/kernel1/linux-5.19.9.tar.xz
cd /home/saksham/kernel1
tar -xvf linux-5.19.9.tar.xz
cd linux-5.19.9
make mrproper
cp /home/saksham/config/.config /home/saksham/kernel1/linux-5.19.9
make -j$(nproc)
