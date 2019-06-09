echo GENERATING NEW SSH KEY...
ssh-keygen -t rsa -b 4096 -C mescue@pdx.edu
\n
\n
\n
eval $(ssh-agent -s)
ssh-add ~/.ssh/id_rsa
echo
echo COPY THIS TO GITHUB:
cat ~/.ssh/id_rsa.pub
exit
