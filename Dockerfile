FROM ubuntu:18.04

USER root

# Configure Registry
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections

# Install Qt/KDE libraries
RUN apt-get -y install g++ make kdelibs5-dev libkf5kdelibs4support-dev \
    qt5-default qt5-qmake libkf5configcore5 libpackagekitqt5-dev cmake \
    extra-cmake-modules gettext appstream \
  && rm -r /var/lib/apt/lists/* \
  && apt-get clean \
  && apt-get -y autoremove

# Install NPM Packages
RUN curl -sL https://deb.nodesource.com/setup_10.x | bash - \
  && apt-get install -y nodejs \
  && npm install -g stylus

RUN useradd -G root -ms /bin/bash dev

USER dev

CMD ["/bin/bash"]
