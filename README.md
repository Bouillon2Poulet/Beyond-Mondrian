<div id="top"></div>
<br><br>
<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/Bouillon2Poulet/TeamGolem">
    <img src="assets/textImage/logo.png" alt="Logo" width="703" height="141">
  </a>
  <h3 align="center">Bouillon2Poulet - Rambogoss - SlayerOfShadow</h3>
  <br>

  <h3 align="center">README</h3>
  <p align="center">
    A guide to install and use <i>Beyond Mondrian</i><br>
    <a href="https://github.com/othneildrew/Best-README-Template"><strong>View a demo»</strong></a> <!--Mettre bon lien-->
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
        <li><a href="#play">Play</a></li>
      </ul>
    </li>
    <li><a href="#main-functionalities">Main functionalities</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]](https://example.com)

We worked as a team of 3 on this "Thomas was alone" like game. <i>Beyond Mondrian</i> uses basic functionalities of  Mike Bithell's original game and takes them further by adding new stuffs such as levels, moving platform, musics and visual elements.
Created for an IMAC school project, we are proud to present you the fruit of a one month labour :smile:
We also want to shout out Steeve and Enguerrand who has been great helps during the development.

This README will help you through installation and use of <i>Beyond Mondrian</i>. It has been done thanks to <a href="https://github.com/othneildrew/Best-README-Template">othneildrew's Best README Template</a>, big up :smile:

<p align="right">(<a href="#top">back to top</a>)</p>



### Built With
Because we worked on Linux (Ubuntu and Mint) for this project, we advice you to do the same as long as we don't realy know how it will react on other OS.

* [C](https://www.learn-c.org/)
* [gcc](https://gcc.gnu.org/)
* [make](https://linuxhint.com/install-make-ubuntu/)
* [OpenGL](https://www.opengl.org/)
* [SDL2](https://www.libsdl.org/download-2.0.php)
* [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

### Prerequisites
* First of all, let's upgrade our all outdated packages with :
```sh
npm sudo apt update
```

In order to compile our source code, we'll need to install :
* gcc compiler and make
  ```sh
  npm sudo apt install build-essential
  ```

* OpenGL library
```sh
npm sudo apt-get install freeglut3-dev
```

* SDL2 and all its libraries
```sh
npm sudo apt install libsdl2-2.0-0 libsdl2-gfx-1.0-0 libsdl2-image-2.0-0 libsdl2-mixer-2.0-0 libsdl2-net-2.0-0 libsdl2-ttf-2.0-0
```


### Installation
1. Clone the repo
   ```sh
   git clone https://github.com/Bouillon2Poulet/TeamGolem
   ```

2. Make clean and make main
* at the root of the TeamGolem file :
  ```sh
  make clean
  ```
  ```sh
  make main
  ```

<p align="right">(<a href="#top">back to top</a>)</p>



## Play

In order to play to <i>Beyond Mondrian</i>, you will have to execute from terminal the bin/main.out file.
at the root of the TeamGolem file :
  ```sh
  ./bin/main.out
  ```

<p align="right">(<a href="#top">back to top</a>)</p>


<!-- CONTACT -->
## Contact

Bouillon2Poulet - [@your_instagram](https://www.instagram.com/consomme2poyo/?hl=af) - romain.serres@edu.univ-eiffel.com

<p align="right">(<a href="#top">back to top</a>)</p>


