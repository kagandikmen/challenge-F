# ImageMagick 7 Notes

for greyscale png to bmp:

	magick source.png -colorspace Gray -colors 256 BMP3:target.bmp

for raw (512x512) to png conversion:

	magick -size 512x512 -depth 8 -define quantum:format=signed gray:source.raw -auto-level target.png
	
for png to raw conversion (works for jpg as well): 
	
	magick source.png -alpha off -depth 8 target.rgb
	(target file has to have the extension .rgb, but can just be renamed after the process)
	
If magick says unexpected end of file, then reduce the depth

If magick creates multiple target files, then increase the depth
	
for sample raw images (as of 2024-09-02):

	https://eeweb.engineering.nyu.edu/~yao/EL5123/SampleData.html
	https://links.uwaterloo.ca/Repository/
	
to convert rgb jpg to greyscale jpg:
	
	magick source.jpg -grayscale average target.jpg
