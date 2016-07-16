# Maintainer Brenton Horne <brentonhorne77 at gmail dot com>

pkgname=cpp-math-projects
_pkgname=CPP-Math-Projects
pkgver=7839fc2
pkgrel=1
pkgdesc="Simple pendulum solver written in C++"
arch=('i686' 'x86_64')
license=('GPLv3')
depends=('octave' 'gnuplot')
makedepends=('gcc' 'make')
url="https://github.com/fusion809/CPP-Math-Projects"
source=("git+${url}.git")
sha256sums=('SKIP')

pkgver() {
  cd "${srcdir}/${_pkgname}"
  git rev-parse --short HEAD
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
 find ${srcdir}/${_pkgname} \
  -name "*.o" -exec cp '{}' ${pkgdir}/usr/share/CPP-Math-Projects \; \
  -name "*.gp" -exec cp '{}' ${pkgdir}/usr/share/CPP-Math-Projects \; \
  -name "*.sh" -exec cp '{}' ${pkgdir}/usr/share/CPP-Math-Projects \;
}
