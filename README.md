# geometries_fis

======= LIBIGL ================

cd libigl/

mkdir build

cd build

cmake -DLIBIGL_WITH_CGAL=ON ../ -DCMAKE_BUILD_TYPE=Release          -DLIBIGL_USE_STATIC_LIBRARY=ON          -DCMAKE_INSTALL_PREFIX=/usr/local/

make -j12

sudo make install


cd /home/mqadri/libigl (or where you cloned libigl library)

sudo cp -r ./include/igl/*.cpp /usr/local/include/igl/

=========== CGAL ====================

cd libigl/external

cd cgal

mkdir build

cmake ..

make -j12

sudo make install

=========== 

To be confirmed: the cgal version that comes with libigl is version 4 so when we check examples online we need to check examples for version 4



