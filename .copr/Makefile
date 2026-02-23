.PHONY: srpm

SPEC := fio.spec
NAME := fio
VERSION := 3.5

srpm:
	dnf install -y git
	set -e && \
	TMPDIR=$$(mktemp -d) && \
	trap "rm -rf $$TMPDIR" EXIT && \
	GIT_SHORT=$$(cd $(CURDIR) && git rev-parse --short HEAD) && \
	GIT_DATE=$$(cd $(CURDIR) && date -u -d "$$(git log -1 --format=%ci)" +%Y%m%d 2>/dev/null || date -u +%Y%m%d) && \
	cd $(CURDIR) && \
	git archive --prefix=$(NAME)-$(VERSION)-$${GIT_SHORT}/ HEAD | \
		gzip > $${TMPDIR}/$(NAME)-$(VERSION)-$${GIT_SHORT}.tar.gz && \
	sed -e "s/@@GIT_SHORT@@/$${GIT_SHORT}/g" \
	    -e "s/@@GIT_DATE@@/$${GIT_DATE}/g" \
	    $(CURDIR)/$(SPEC) > $${TMPDIR}/$(SPEC) && \
	rpmbuild -bs $${TMPDIR}/$(SPEC) \
		--define "_sourcedir $${TMPDIR}" \
		--define "_srcrpmdir $(outdir)"
