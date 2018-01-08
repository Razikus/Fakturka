DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
LIBS="$DIR/libs"
smtpClient="$LIBS/smtpclient"
mkdir -p $LIBS

if [ -d "$smtpClient" ]; then
	cd $smtpClient
	git pull 
else 
	git clone https://github.com/bluetiger9/SmtpClient-for-Qt.git $smtpClient
fi

rm -rf $DIR/src/libs
cp -r $LIBS $DIR/src/

