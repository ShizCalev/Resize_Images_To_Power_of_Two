Recursively scans a folder for images that have a dimension which is not a power of 2, and resizes them up to the next power of 2 if needed (using a hermite interpolation filter to maintain pixel sharpness & color.)

Built for my [MGS2 PS2 Texture re-exporting project](https://github.com/dotlessone/MGS2-PS2-Textures)

Requires [ImageMagick](https://imagemagick.org/) & its optional development headers to be installed.
