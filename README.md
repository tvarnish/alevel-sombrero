# Sombrero

> This repository has been archived. It serves as a place to preserve my original A-Level Computer Science Project, Sombrero, as it was when I completed it. Any future changes to this project will be made in a separate repository.

Sombrero is my A-Level Computer Science project (AQA), focused on simulating the three-dimensional N-Body Problem. Basic documentation can be found at [alevel-sombrero.readme.io](https://alevel-sombrero.readme.io), and reference for the Simulation class can be found in the Reference section of that site.

<p align="center">
  <img width="200" src="https://i.imgur.com/lDOrYA1.png">
</p>

## Getting Started
These instructions will get a copy of the project running on your local machine, for development and testing purposes (I haven't written the `make install` command yet).

### Prerequisites
In order to produce the output `.mp4` files, you will need to have `avconv` installed.

```
sudo apt-get install libav-tools
```

If you don't have `cmake` installed already, you will also need to install it.

```
sudo apt-get install cmake
```

You will also need a copy of `pngwriter` installed on your machine.

```
sudo apt-get install libpng12-dev libfreetype6-dev
git clone https://github.com/pngwriter/pngwriter.git
cd pngwriter
cmake -DCMAKE_INSTALL_PREFIX=/usr/
sudo make install
```

It is also important to note that you will require **g++-4.9** in order to compile Sombrero (as regex is used). You can check your installed version of g++ using the following command. If it says that you have 4.9.x installed, you should be good to go!

```
g++ --version
```

If you don't already have g++-4.9 installed, you can install it with the following commands:

```
sudo apt-get install software-properties-common
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install g++-4.9
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.9 50
```

### Installing from source
To download a copy of the repository, you will need to type the following commands:

```
git clone https://github.com/tvarnish/sombrero.git
cd sombrero
make setup
```

## Usage
Once the software has been installed, the program can be run from within the `sombrero` directory using the following command:

```
./sombrero
```

If you wish to time the simulation, you can use `time` on the program, like so:

```
time ./sombrero
```

You can change what the script does by editing the file: `src/testing.cpp`. Once you have changed this file, call `make` in the main directory (`sombrero`), and then run the software as described above. Full scripting / usage notes can be found at [sombrero.readme.io](https://sombrero.readme.io/docs)

## Initialisation files
Initialisation files are comprised of a number of lines, each describing one 'body' in the simulation. Each line must be writen as follows (replacing the text in the example below with a numerical value, e.g. 5 or 4.0e10, etc.):

```
x position,y position,z position,mass,radius,x velocity,y velocity,z velocity
```

So, for example, if we were to have the Sun at the centre of the simulation (currently stationary), we could write:

```
0,0,0,1.989e30,6.955e8,0,0,0
```

If you wish to write a comment in the file, you can use // to indicate that anything after the double forward slash on that line is a comment. For example:

```
0,0,0,1.989e30,6.955e8,0,0,0 // An example of a comment
// Another example of a comment
```

You may also place any whitespace (except a newline!) between each of the parameters and the commas, if you wish.

## Output
The output files generated by the software (in the format `simulationname_output.csv`) follow the same structure as the initialisation files supplied to the software, as described above.

Sombrero will also produce an `.mp4` file of the simulation (still images from the simulation can be found the `images/` directory).
