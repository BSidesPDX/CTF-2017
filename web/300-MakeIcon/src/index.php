<?php

if (count($_FILES) == 1){

$file=$_FILES["file"]["tmp_name"];
$format=$_POST["format"];
$size=intval($_POST["size"]);
if ($size > 768){
    echo "Error size too big.";
    exit();
}
if (!ctype_alnum($format)){
    echo "Error invalid format.";
    exit();
}
$size=$size . "x" . $size;
header("Content-Type: image/jpeg");
echo `convert $format:$file -resize $size jpeg:-`;
exit();
}

?>
<!DOCTYPE html>
<html>
<head>
<style>
body {
 font-family: arial;
 line-height: 1.5;
 letter-spacing: 2px;
}
</style>
</head>
<body bgcolor="#998877">
<center><h1>App Icon Converter!</h1>
<h5>Version 2016.3717</h5>
<hr>
<p>Use this tool to convert images to app icons!</p>

<form action="index.php" method="post" enctype="multipart/form-data">
<table>
<tr><td>
Select image to upload:
</td><td>
    <input type="file" name="file">
</td></tr>

<tr><td>
Select <b>input</b> image format:
</td><td>
<select name="format">
<option value="AAI">AAI</option>
<option value="ART">ART</option>
<option value="AVS">AVS</option>
<option value="BGR">BGR</option>
<option value="BMP">BMP</option>
<option value="CALS">CALS</option>
<option value="CIN">CIN</option>
<option value="CLIP">CLIP</option>
<option value="CMYK">CMYK</option>
<option value="CUR">CUR</option>
<option value="DDS">DDS</option>
<option value="DPX">DPX</option>
<option value="EPT">EPT</option>
<option value="EXR">EXR</option>
<option value="FAX">FAX</option>
<option value="FITS">FITS</option>
<option value="FTS">FTS</option>
<option value="GIF">GIF</option>
<option value="GRAY">GRAY</option>
<option value="HDR">HDR</option>
<option value="HRZ">HRZ</option>
<option value="ICON">ICON</option>
<option value="IPL">IPL</option>
<option value="JBIG">JBIG</option>
<option value="JPEG">JPEG</option>
<option value="MAP">MAP</option>
<option value="MASK">MASK</option>
<option value="MAT">MAT</option>
<option value="MIFF">MIFF</option>
<option value="MONO">MONO</option>
<option value="MPC">MPC</option>
<option value="MPEG">MPEG</option>
<option value="MSL">MSL</option>
<option value="MTV">MTV</option>
<option value="MVG">MVG</option>
<option value="NULL">NULL</option>
<option value="OTB">OTB</option>
<option value="PALM">PALM</option>
<option value="PCD">PCD</option>
<option value="PCL">PCL</option>
<option value="PCX">PCX</option>
<option value="PDB">PDB</option>
<option value="PDF">PDF</option>
<option value="PFM">PFM</option>
<option value="PICT">PICT</option>
<option value="PNG">PNG</option>
<option value="PNM">PNM</option>
<option value="PS">PS</option>
<option value="PSD">PSD</option>
<option value="RGB">RGB</option>
<option value="RGF">RGF</option>
<option value="SGI">SGI</option>
<option value="SIX">SIX</option>
<option value="SIXEL">SIXEL</option>
<option value="SUN">SUN</option>
<option value="SVG">SVG</option>
<option value="TGA">TGA</option>
<option value="TIFF">TIFF</option>
<option value="TXT">TXT</option>
<option value="UYVY">UYVY</option>
<option value="VICAR">VICAR</option>
<option value="VID">VID</option>
<option value="VIFF">VIFF</option>
<option value="VIPS">VIPS</option>
<option value="WBMP">WBMP</option>
<option value="X">X</option>
<option value="XBM">XBM</option>
<option value="XPM">XPM</option>
<option value="XWD">XWD</option>
<option value="YCbCr">YCbCr</option>
<option value="YUV">YUV</option></select>
</td></tr>
</table>
<input type=hidden name="size" value="64">
<input type="submit" value="Convert to JPEG icon!" name="submit">
</form>
</body>
</html>

