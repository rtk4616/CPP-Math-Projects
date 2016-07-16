# Maintainer Brenton Horne <brentonhorne77 at gmail dot com>

pkgname=cpp-math-projects
_pkgname=CPP-Math-Projects
pkgver=5e8cc47
pkgrel=1
pkgdesc="Simple pendulum solver written in C++"
arch=('i686' 'x86_64')
license=('GPL3')
depends=('octave' 'gnuplot')
makedepends=('gcc' 'make')
url="https://github.com/fusion809/${_pkgname}"
source=("git+${url}.git")
sha256sums=('SKIP')

pkgver() {
  cd "${srcdir}/${_pkgname}"
  git rev-parse --short HEAD
}

prepare() {
  cd ${srcdir}/${_pkgname}/Simple-Pendulum
  sed -i -e 's|simple-pendulum.gp|/usr/share/CPP-Math-Projects/simple-pendulum.gp|g' *.cpp
  cd ../Simple-Pendulum-Adjusted
  sed -i -e 's|simppenadj.sh|/usr/share/CPP-Math-Projects/simppenadj.sh|g' *.cpp
  sed -i -e 's|simppenadj.gp|/usr/share/CPP-Math-Projects/simppenadj.gp|g' *.sh
}

build() {
 cd $srcdir/$_pkgname/Simple-Pendulum
 make
 cd ../Simple-Pendulum-Adjusted
 make
}

package() {
 cd $srcdir/$_pkgname
 install -dm755 ${pkgdir}/usr/share/CPP-Math-Projects
 install -dm755 ${pkgdir}/usr/bin
 find ${srcdir}/${_pkgname} \
  -name "*.o" -exec cp '{}' ${pkgdir}/usr/share/CPP-Math-Projects \; \
  -or -name "*.gp" -exec cp '{}' ${pkgdir}/usr/share/CPP-Math-Projects \; \
  -or -name "*.sh" -exec cp '{}' ${pkgdir}/usr/share/CPP-Math-Projects \;
 chmod 755 -R ${pkgdir}/usr/share/CPP-Math-Projects/*

 cd ${pkgdir}/usr/bin
 ln -sf ../share/CPP-Math-Projects/simple-pendulum.o simple-pendulum
 ln -sf ../share/CPP-Math-Projects/simppenadj.o simppenadj
}
