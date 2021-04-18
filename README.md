# geometries_fis

cd libigl/
mkdir build
cd build
cmake -DLIBIGL_WITH_CGAL=ON ../ -DCMAKE_BUILD_TYPE=Release          -DLIBIGL_USE_STATIC_LIBRARY=ON          -DCMAKE_INSTALL_PREFIX=/usr/local/
Make -j12
 Sudo make install

Cd libigl/external
Cd cgal
Mkdir build
Cmake ..
Make 
Sudo make install


Cd /home/mqadri/libigl
sudo cp -r ./include/igl/*.cpp /usr/local/include/igl/


To be confirmed: the cgal version that comes with libigl is version 4 so when we check examples online we need to check examples for version 4



