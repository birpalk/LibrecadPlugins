echo "enter the name of plugin:"

read plugin_name
while [  -d $plugin_name ]              #check if the same folder exits 
  do
	{
	echo " plugin exist, enter some other name:"
	read plugin_name
	}
done

mkdir $plugin_name
path=$(pwd)
cp -r sample/* $path/$plugin_name/
cd $plugin_name
#tr 'sample' '$plugin_name'
sed -i "s/sample/$plugin_name/g" $path/$plugin_name/*

mv sample.cpp $plugin_name.cpp
mv sample.h $plugin_name.h
mv sample.json $plugin_name.json
mv sample.vcxproj $plugin_name.vcxproj 
mv sample.pro $plugin_name.pro
exit
