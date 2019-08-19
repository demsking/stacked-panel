# HPX Stacked Panel

A fully stylized StackedWidget implementation

## Build

```sh
# Create the hpx-stacked-panel:ubuntu image
docker build . -t hpx-stacked-panel:ubuntu

# Compile Setup
mkdir build
docker run -it --rm -v $(pwd):/src -w /src/build hpx-stacked-panel:ubuntu cmake ..

# Compile HPX Stacked Panel
docker run -it --rm -v $(pwd):/src -w /src/build hpx-stacked-panel:ubuntu make

# Install the library
sudo make -C build install

# Package the library
docker run -it --rm -v $(pwd):/src -w /src/build hpx-stacked-panel:ubuntu make pack
```

## Contribute

Contributions to HPX Stacked Panel are welcome. Here is how you can contribute to HPX Stacked Panel:

1. [Submit bugs or a feature request](https://gitlab.com/demsking/stacked-panel/issues) and help us verify fixes as they are checked in
2. Write code for a bug fix or for your new awesome feature
3. Write test cases for your changes
4. [Submit merge requests](https://gitlab.com/demsking/stacked-panel/merge_requests) for bug fixes and features and discuss existing proposals

## Versioning

Given a version number `MAJOR.MINOR.PATCH`, increment the:

- `MAJOR` version when you make incompatible API changes,
- `MINOR` version when you add functionality in a backwards-compatible manner, and
- `PATCH` version when you make backwards-compatible bug fixes.

Additional labels for pre-release and build metadata are available as extensions to the `MAJOR.MINOR.PATCH` format.

See [SemVer.org](https://semver.org/) for more details.

## License

Copyright (C) 2018 Sébastien Demanou.

Under the GNU General Public License.

Everyone is permitted to copy, modify and distribute HPX Stacked Panel. See
[LICENSE](https://gitlab.com/demsking/stacked-panel/raw/dev/LICENSE) file for more details.
