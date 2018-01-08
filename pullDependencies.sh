DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
LIBS="$DIR/src/libs"
smtpClient="$LIBS/smtpclient"
mkdir -p $LIBS

if [ -d "$smtpClient" ]; then
	cd $smtpClient
	git pull 
else 
	git clone https://github.com/Razikus/SmtpClient-for-Qt.git $smtpClient
fi

