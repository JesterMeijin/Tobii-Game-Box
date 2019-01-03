#!/bin/bash

# extract project path in gitlab
PROJECT_PATH=`echo ${CI_BUILD_REPO} | sed "s~http[s]*://[^/]*\(.*\).git$~\1~" | sed 's-/--'` 

SFTP="sftp -P 2223 gitlab@static.projectsforge.org:/gitlab/"

# Extract version and date from LaTeX document class
FILES_VERSION=$(grep '\\def\\polytechfileversion' polytech/polytech.cls | sed 's~\\def\\polytechfileversion{\(.*\)}~\1~' )
FILES_DATE=$(grep '\\def\\polytechfiledate' polytech/polytech.cls | sed 's~\\def\\polytechfiledate{\(.*\)}~\1~' | sed 's~/~.~g')

# Create the archive
ARCHIVE="polytech-$FILES_VERSION-$FILES_DATE.zip"
zip -r $ARCHIVE polytech/

# Upload archive
(
    IFS='/' read -r -a array <<< "$PROJECT_PATH"; 
    for element in "${array[@]}"; do 
        echo "mkdir $element";
        echo "cd $element"; 
    done
    echo "put $ARCHIVE"
) | $SFTP


# Retreive archive list
rm oldlist.txt
(
    IFS='/' read -r -a array <<< "$PROJECT_PATH"; 
    for element in "${array[@]}"; do 
        echo "mkdir $element";
        echo "cd $element"; 
    done
    echo "get list.txt oldlist.txt"
) | $SFTP

# Create the new list
echo $ARCHIVE > list.txt

BASEURL="https://static.projectsforge.org/gitlab/polytech/polytech/"

# Check for missing files
cat oldlist.txt | while read f; do
    if [ ! "$ARCHIVE" = "$f" ]; then
	curl -f -u $NEXUS_USER:$NEXUS_PASSWORD $BASEURL/$f > /dev/null 2> /dev/null
	result=$?
	if [ "$result" = "0" ]; then
    	    echo "Found $f"
    	    echo $f >> list.txt
	else
    	    echo "File $f is missing"
	fi
    fi
done

# Create the index
echo "<html><body><h1>Liste des fichiers disponibles</h1><ul>" > index.html
FIRST=1
cat list.txt | sort -r --version-sort | while read f; do
    if [ "$FIRST" = "1" ]; then
	FIRST=0
	echo "<li><a href='$f'><b><font color="red">$f</font><b></a></li>" >> index.html
    else
	echo "<li><a href='$f'>$f</a></li>" >> index.html
    fi
done
echo "</ul></body></html>" >> index.html

# Upload files
(
    IFS='/' read -r -a array <<< "$PROJECT_PATH"; 
    for element in "${array[@]}"; do 
        echo "mkdir $element";
        echo "cd $element"; 
    done
    echo "put list.txt"
    echo "put index.html"
) | $SFTP



