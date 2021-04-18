# geometries_fis

cd libigl/
mkdir build
cd build
cmake -DLIBIGL_WITH_CGAL=ON ../ -DCMAKE_BUILD_TYPE=Release          -DLIBIGL_USE_STATIC_LIBRARY=ON          -DCMAKE_INSTALL_PREFIX=/usr/local/
make -j12
sudo make install

cd libigl/external
cd cgal
mkdir build
Cmake ..
make -j12
sudo make install


cd /home/mqadri/libigl (or where you cloned libigl library)
sudo cp -r ./include/igl/*.cpp /usr/local/include/igl/


To be confirmed: the cgal version that comes with libigl is version 4 so when we check examples online we need to check examples for version 4



