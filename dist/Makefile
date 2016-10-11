
dist-arch:
	git clone git+ssh://aur@aur.archlinux.org:22/termplot.git
	pwd
	cp -i -a arch/. termplot
	cd termplot && \
		makepkg --printsrcinfo > .SRCINFO && \
		git add PKGBUILD .SRCINFO .INSTALL && \
		git commit && \
		git push origin master
	rm -rf termplot
