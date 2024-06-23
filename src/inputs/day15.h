#include <string_view>

namespace day15 {

using namespace std::literals;

inline constexpr auto sample =
    R"(rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7)"sv;

inline constexpr auto input =
    R"(xxcc=8,jq=4,qbns=7,qgp-,jb=4,mxh=3,ltf-,xlkb-,ff=5,fjrp-,nl=8,lmhb-,tjfk-,qnn-,fz-,hjp-,msl=6,vmm-,dj=6,db-,knp-,lkks-,jq=5,db-,jx-,tp=1,gtx=7,mktfz-,fx-,jk=2,ddk=6,rzpt-,qpn=5,hxl=6,vl-,xpl=1,mbrmr=6,mnx-,jbgf-,lmpxsn=8,psf-,vv=6,nkccfg=7,xg-,ss-,sx=5,tc-,vmcsh=8,vnz-,pgpzq=9,jzhvv=7,nkccfg=9,kzzn-,lrkmv=7,vgv=9,vb=9,jq=1,jv=8,chfsm-,htqt=9,zk-,gc=5,mt=7,mcpkb-,fx=6,mktfz-,sbx-,psb-,df=4,jv-,xh-,zzqmg=2,mxtz-,kr-,psr=6,mxtz-,px-,klnvl-,vgv-,cspg=9,sspm-,tt-,kqql-,xznvs-,vsd-,td=4,kbmc=4,ggf-,bltn-,ks=9,rf-,jx-,qgp-,pb=5,cpb=5,tn=3,sx-,sh-,xc-,hch-,vmm=9,tbc-,mktfz-,hc=1,smks-,hh=6,jgrd-,vgc-,cpb-,gc=5,xfg=3,jq=5,qs=5,gnhjs=7,gg=4,jbgf-,clpc-,kjcqvr-,bmhs-,bt-,bbth-,fn-,nrvg-,zgs=2,jq=5,dsp=9,gdx-,gdc-,grkk=5,mhqzc-,pl-,lrdkf=1,rj-,pjct=2,scx-,cxz=9,dxtvkd=9,xj=3,pssx=7,vkf-,jgs=3,hgpd-,vm-,ggf=2,xt=6,jfrkh=5,flh=6,hgjhv=2,grkk-,gr-,vcp=8,hgpd-,gxc-,ftp=8,xsbg=2,vnk=2,sq=8,mnpbcf-,sgv=4,dbs=7,lzmb=7,vmcsh=6,rtclsf-,ngs-,xjznm-,vss=7,qq-,vg-,bt-,zgs-,xpl-,qpn=7,lk=1,qq-,vxlgph-,kp=7,ctg=3,gpjm=3,dcmx-,kglvq=7,rjrm-,rncmzp-,fn=2,stg=9,mnpbcf=4,sdg=7,nkzzc-,gpt-,srb=2,sf-,bdlt=2,mcpkb-,mdvnr-,bclt=3,dgk-,zsg=3,pzjgls-,bt=4,mz=5,hd=4,ljr-,clpc-,qpn=8,fjrp=9,cspg=9,jb-,xsh=3,jnps=1,lmhb-,dk-,rmm-,shx-,vnk-,gtx=2,hvvh-,jkz=7,mch=2,bltn-,ghk-,pjl=9,gpt-,fjrp=4,cpb-,thn-,sdbj=5,hb=1,qjjfz=2,kz=6,hb-,jc-,msb=3,tc=8,dgf=6,vsm-,rzpt-,sbg-,hhz=3,qjjfz-,vsd=9,ztcgrm=6,gzx=1,jkz-,qpn-,ngs-,vp-,bg-,kpv=1,xg-,ph=6,lmhb=4,xh-,lrc-,hgv=9,msb=4,ttk=2,vxr-,td-,rt-,kf=1,pnq=7,bzk=2,vzp-,hvs-,cpz=6,sjdkl-,vnz=9,lkks=5,dgk-,vmm-,psf-,ckcslv=5,vv=1,njv=1,dtdk-,gg-,scx=6,gxs=1,bt=7,dqns=3,sdg-,rp=1,bnn=3,sq-,ttk=9,bdlt=6,lkks-,cx-,mbrmr-,jc-,rl=3,psr-,ctg=9,vb=1,pssx-,lnc=4,crxg-,sspm-,fx-,gr-,vjv=8,bl=5,pc=4,hb=3,mkn-,fhp=5,kpmfqs-,vxlgph-,khsf-,lnc-,gpjm-,jnps=1,nfv=9,dxtvkd-,kd-,jgs-,ssp-,kzt=9,ss=3,lcq=7,nks=4,nsnn=9,msl=8,dv=4,rzxt=6,mfx=6,rbpp-,grkk-,lvfdjv-,qx-,gxd=3,ckrt=1,pz-,jb-,zbc-,hh-,jvjdbb-,ztcgrm=5,xsbg-,tv=8,ftp=1,bzk=3,jhm-,xxcc=3,rxrt=2,rq=7,rt-,vphf=6,xm=3,srb=5,hzq=6,zxz-,mnt=1,vlnd=4,fr=5,dbs=6,bzp=1,rbt=4,nj=5,lvfdjv=2,qb=6,hzq-,ckrt-,dgpf=5,fl=7,lf=2,svg-,kbmc=1,fz=3,kpd=3,kf=2,mnx=7,bjd=2,dkv-,vmm=9,zhd-,xvh-,pnq-,lvfdjv-,xzf-,pb=8,ctg-,mch=8,bjd=7,vzp-,bdlt=2,dv=7,xc-,bzp=2,xfg-,kz=7,nmn=9,kbqc-,mxh-,gfjrh=6,dnj-,bpf=3,qqj=6,dnc-,gc-,jq=5,nmrt=1,hd-,dz=5,hd-,dgf=3,tn-,pbdd-,nn-,xc-,cxz=3,vg-,nkccfg-,xvh=9,gxmgld=5,jq=2,kgk=4,kzzn-,ltf-,hmv-,ttk-,rmm=8,xpl=3,nvx=8,hzq-,lrc=4,gdx=2,zzx=5,gg=6,kzt=4,xvh=9,cc-,rfs=3,smnh-,kpb-,nsnn-,pl=9,bpf-,jv=5,ng=8,gxc-,rzxt=9,bbth-,lnc=5,nn=2,cxxrc-,vbs=7,dkv=2,sbg=6,qfpf=5,crxg-,bt=7,vc-,qrr-,gtm=5,ltf-,lrdkf=3,gqgzxf-,lzmb-,xkt=4,hh=9,sn=4,hr-,zdjgj-,jx=2,cpz-,hjp-,hh=6,vtms-,pgr-,jq-,mxh=7,kf=5,lbdrk-,kqql-,vjv-,jfsg=5,vc-,mnt=7,xb=9,hgjhv-,mxtz=5,zgs=2,zhd=5,vdfx-,fx=3,mf=6,sck-,kf-,gr-,kpv=5,xt-,msb=2,hjx-,mxh=1,tc-,rvs-,vzp=5,cl-,fl-,ddn-,vcp=1,rjk=2,qq=1,jgs=4,slds=5,jdb-,grkk=2,vmcsh-,nmq-,dsp=3,lmpxsn-,hch-,xgrs-,tt-,vxr=3,hch=6,mdn=6,cc=7,dv-,dhjv-,vgc-,qbns=6,psr-,vsm=7,mhqzc-,vxlgph=2,vc=2,vjl=9,rfs-,gpjm=6,vfjdpr-,hjx-,xvh=8,fkrs=1,lk-,sccd-,lmhb=3,pt=1,tc-,hzq-,khsf-,bl-,zdtb=6,hbg-,gq=8,dgpf-,kpd-,ddk=6,rbpp=2,jbgf=6,xzf=9,td=4,vl-,qqj=2,dgf-,xvh-,fqqx=7,kqql=9,lkks-,nn-,xt=8,sh=5,kp-,kn-,bmxzp-,bl-,nks-,kn=9,ml-,hxl-,qfpf-,tsvtm=4,kglvq=3,pgpzq-,kvkdr=1,fr-,bfsnt-,gxc-,mbp=4,gk=9,bclt=1,fk-,kk-,dd-,sf-,hd-,snz=2,tjfk-,hb=6,mdvnr-,ngs-,sccd=6,sh=5,lnc=1,jf-,smks=5,rxrt-,bb-,xlx-,nmrt=7,pxlvz-,bjd=6,nl=1,pssx-,tc=7,nmrt-,xsh=6,nfv=5,qr=3,sgvz-,jhm=6,xlkb-,bpf-,fv-,mv=2,xg=2,vxlgph-,msb=6,pmp=8,qq-,sck=2,qbpq-,qr-,dbs=6,pz=3,dkv=1,kq=4,vzp=1,lzmb-,rbt=2,hjp=3,kqql-,df-,mjx-,rtclsf=4,ssj-,hz-,lcq=8,rbt=4,rz-,tq=1,lzmb-,ljr=9,hgqr-,zhd=1,hg-,tqhs-,mk-,cx-,xkt=9,qq=9,bfsnt-,gq-,ddn=7,qhsj-,jvx-,qqj=8,fpp=8,qbpq-,sspm=6,dgk=7,gxmgld=2,vnk-,dsfb-,vjv-,sdbj=1,sq=5,hjp=6,jhm-,jxf-,vv-,df=8,nsnn=4,kf=3,gdc-,ntgd-,jnps-,ttk-,ncndp=1,hjp-,qx=3,gq-,tv-,bnn-,fpp=2,fjrp=3,ks=2,ndq-,qrr-,fkrs=3,kz=9,mjx-,qjjfz=9,kr-,hg-,szxdt=9,qb=2,kzzn-,qqj-,zv-,tb=4,nkr=4,rnk-,mxh=5,vmm=5,xh-,qrr=4,gr=5,pxhnxj=9,vgc-,sck=2,hjp-,mcl-,rjrm-,rmm-,cspg-,vc=2,srb=4,mxtz=1,mnt-,tqb-,dv=1,cp=7,gfjrh-,fr=2,nl=4,mcl-,vmh-,nsm-,ssp=4,nvx=5,lrkmv-,hc-,dsp=1,mz=9,sjdkl=9,jpn-,kglvq=1,fl-,flp=8,mf=5,dg-,sccd=6,cb-,ngs=6,tjfk=9,px-,svg=4,gfjht-,nbd=3,sccd-,hjx=6,xsh=2,pjl=8,lrc-,bbth-,vvl-,kp-,sx=7,ngqh-,chv=2,sdg=8,zjhht-,ghk=7,zsgl=6,tzz-,zg=8,dbs=5,fbng=6,tv-,qx-,hgjhv-,hbg=5,mdn-,hmv=1,hhz=5,xvs=2,vzp-,zjhht-,tls=5,tzz-,zf=9,rvr=3,qbns=2,bqctt=7,prf-,xsh=3,hbg=5,pz=6,nsm-,ks=8,qx-,smks=5,tg=8,krl-,mktfz-,rxrt=6,sgvz-,zxz-,hp-,hxl=2,fjrp=3,dj=4,mz-,mk=1,rxrt=2,bjd=8,dk=3,fqqx=5,snz-,kn=5,vxlgph=5,vg-,fjrp=6,mcpkb=2,szx=8,knp=5,dv-,qg=6,jvjdbb-,rlfgd=4,hvs=5,gpjm-,cb=7,dd=7,vfjdpr-,hvs-,hg=2,lpd=8,zbc-,mth-,qndj-,bk-,xgrs=6,vvl-,ljr-,sbx=8,td-,pb-,sft-,gq=1,mf=2,hxl-,hbg=5,jpn-,lpd=1,rf=4,mdqh-,mr=3,rmm-,bpf-,mnpbcf=2,xsh-,sspm-,gzx=6,clpc=4,xlkb-,vgc=1,xgrs=9,gxs=5,ftlcft-,sj=3,lkks=4,xg-,vd-,mhx=8,hqlkpl=3,qqh=3,tb=7,glmzc-,td-,lrpxp=4,pgpzq-,jb-,dvh=8,bmxzp-,bzsx=8,dkv=6,hd=4,psf-,js=9,kpb-,gxd=4,jgs=7,jvjdbb=2,ftp-,gpjm-,hgv-,chfsm-,pssx=9,scx-,mjx-,lvfdjv-,gxmgld=1,bltn=2,mcpkb-,dqns=9,nsnn=6,jxf-,rxq-,rlfgd=4,slds=8,qqj-,snz=4,xsh=7,df=6,bt-,td=6,jpb-,dhjv=8,gfjrh-,rd=2,zdjgj-,mhx-,cl-,tzz=9,vzp=7,qndj-,rfs=5,lcm-,zj-,mcpkb=6,td=5,knp-,nrvg=2,tc=6,mxtz=6,mnt=8,smnh=9,ssj=5,pjct=8,zjhht=7,tt-,gnhjs=1,vlnd-,psb=5,gtm=4,fr-,dv-,rp=8,rmm-,tq-,cp=6,ssp=1,js-,sccd=5,mktfz-,mch-,vjl-,tcqz-,gtm-,qndj=1,vdl-,km-,zk-,ff-,zdtb=4,gxd-,zdjgj-,svg-,vvl-,cxxrc=4,rvs-,pc-,xj-,qqh=8,tqhs=3,hg=7,kzzn-,jc-,dgk=4,jgrd=7,kf-,vp=1,rzcx-,rvr-,mfx-,ckrt=9,xdk=7,njv-,msl-,lrpxp-,kp=3,xj=8,zzqmg-,ml=9,bltn=8,srb=7,mzfl=6,bb=6,pxlvz-,hp-,vcp-,xp=2,zdks=6,jgs-,rt-,srb-,tcqz-,fhp-,hjx-,kb-,hhz-,mnx-,kbqc=1,hxl=2,hp=8,jgrd=8,dk=7,gnhjs=3,zfhmj=4,pzjgls-,rzcx-,vg=2,scx=7,tsvtm-,bdlt-,xsbg-,lcm=8,km=7,rncmzp-,psf=9,sbg-,gxc=5,xfg-,lzmb=7,fv-,ljr=1,xqgl-,ts=6,sq=9,xzkj=6,ljr-,fl=6,kn-,vp=6,smks-,vpnk-,jf-,sh-,qpn-,bbk=4,td=2,jvx=9,hch-,lk=3,fqlnbc-,szxdt-,hl=4,pgp=8,rncmzp=7,bfsnt=5,rbvl=1,cp=7,qfpf=6,qbpq=1,xdk-,qqj-,mq=7,xkt=3,xsh-,sjdkl=5,zsq-,rjrm=6,nkccfg=8,lls=2,kp-,zf=9,dd-,vhzd=6,vjv=7,vmcsh=7,pfxhxj-,xznvs-,qgt=1,zjhht-,vxr-,bk-,smnh-,xlx=4,hqlkpl=9,dnc=5,jbgf=6,lpd-,mhqzc-,dgf=6,dnj-,cb=1,jgs-,nnkl=4,dvd-,kjcqvr-,pnq=1,vdfx=3,ftp=8,bqblll=1,vjl=1,rvr=8,knp=6,sbvx-,gzx=3,zs=3,zxz-,jbgf=5,stg-,fkrs=1,gtx=8,kgk-,zfhmj=4,mth=1,dj=8,fjrp=9,nj-,zdtb=8,gzx=8,th=7,jkz=1,zdtb=6,mq=9,zsgl=7,xr-,hqlkpl-,zs=8,xvh-,jvjdbb-,hxl=9,ddn=1,qbpq=3,fjrp-,tch=3,th=9,jq-,bl=7,qskn=9,kk-,mhqzc=2,pt-,srb=4,bzp-,lmpxsn-,tn-,clpc-,dcmx-,mxh-,jk=8,rzxt-,zg=8,lk-,hvvh=7,szxdt=8,tls-,pc=3,klnvl-,prf=6,bltn=9,bk-,hl-,sx-,tl-,pdg=5,kzzn-,kq=4,ckcslv=8,vh=8,rtclsf=8,lrkmv-,szx-,cmp=3,jhm=8,cfx-,gc-,ctg-,xkt-,kpmfqs-,vtms-,rfs-,bz-,mhqzc=5,qx-,psb=2,thl=5,dtdk=4,fpp-,xp-,pc-,hhz-,ltf-,nn=3,thn=7,lvfdjv-,bnn=4,rp=9,htqt-,hzq-,xzkj=7,gdc=1,qbpq-,rvr-,cxxrc=5,grkk=5,chv-,gq-,rfs=8,nrvg-,mfx-,kg=8,hgpd=6,nnkl=4,xt-,gbxh-,qs-,krdk-,tm=3,rjrm=8,bdlt=3,gp-,pxlvz=8,jv=7,jkz-,zc-,kglvq=4,fn=2,rnk=4,lqq-,mbp-,jnps=8,hvs-,xlx=2,bzsx-,hp=4,cxxrc=2,ztcgrm-,qx-,qnn-,hgjhv-,xvs=2,jbgf=5,jfrkh-,nbd=2,kk-,bmxzp-,rjk=2,xh-,ssp-,td-,pnq-,df=8,vtms=8,cp=7,kphb-,hd-,xxcc-,dnj-,fz=1,tq=5,df=2,nt=8,hgqr=2,vcp-,mdqh-,vp-,vgc=5,ddn=9,xp=3,vd=6,lrkmv=3,bb-,cpb-,gr=9,fqqx=9,ncndp-,rjrm-,dbs=7,cp-,dk=7,mdvnr-,htzgz=5,fx=5,lcq-,dnc=6,hgpd-,pm=7,vgv-,ps-,gfjrh-,vp-,sgv-,sft-,slds=6,rd=1,htqt=2,sbx=5,xvfc-,mv-,fx-,nkccfg=8,qjz-,nmn-,hh-,sbg=6,smnh=5,jk=8,xgrs=5,th-,mkn-,rmm-,lmhb-,kpd=9,gp=1,vsd-,kzt=7,lcq-,rq-,mnt=8,mn-,kr=1,qfpf-,thl-,hvs=5,zk-,sj=3,dgf-,lcq=2,rncmzp=3,nk-,ncndp-,kr=3,hjx=8,nl=5,mz=4,tqb-,fvpqcp-,pf=7,tp=4,rf-,dgk=1,qgp-,jfrkh=1,vvl=8,ngs-,qjz-,ts-,fz=4,mk=8,xzkj=2,cpz-,mdqh-,slds=2,mhqzc=8,hgjhv=5,fn=5,ts-,hvvh-,vcp-,xzf-,nvx=3,sx-,vsm=3,rzpt=6,dz=8,msl-,lbdrk=6,lmhb=9,nbd-,vxlgph=8,vphf-,pgp-,vsm=9,gc-,tm-,mv-,vjv=4,bj=9,rncmzp=1,chfsm=5,qrr-,bck=2,hxl-,mxtz-,qpcvg=6,ml=2,pf=3,cqs=4,nks-,jkz-,hmv-,qjz=8,mt=5,hqlkpl-,bck-,pb=4,xm-,vjl=3,mr-,gzx-,xzf-,gfjrh-,dg-,lkks-,mkn-,gg-,vld-,fpp-,zg=5,ttk=6,zzx=9,pc-,pc=7,vd-,pxhnxj=8,ckcslv=5,ph-,vfjdpr=4,pm=9,kb-,ntgd=3,km-,svg=7,cpb-,mjx=4,lpd=1,hr=5,dqns-,qgp=3,pb=4,nsnn-,ghk=5,pfsff-,pmp=3,rjrm=4,gbxh-,nn-,sjdkl-,jsz-,tcqz-,zdtb-,sspm-,rbvl=2,jv=6,vv=1,bk-,hbg-,ng=2,nkr-,rv=1,ncndp-,ff=3,vpnk-,ljr=1,xxcc=7,kk=8,hh-,rt=3,lpd=9,vcp=3,mktfz=1,fn=1,ts=7,sccd=6,tch-,kbmc=2,hgpd-,bclt-,lmhb=2,tg-,dsp-,gq-,dz-,thn-,qpn=8,dcmx=9,sn-,gxs-,zk-,gm=5,zk=3,sspm-,mzfl=2,gk-,bzk=6,grkk=7,rfs-,ndq-,hzq-,vd-,tv-,fjrp=7,xxcc=9,hz-,rt=2,vmh-,mz-,dvd=1,szdz-,vmm-,bt-,sh=3,xv-,sft=5,vmcsh-,qqj=1,sck-,gm-,rqzxz-,vzp-,ncndp=6,fkrs=7,tjfk-,tcn=6,ztcgrm-,vl=9,fl=1,khsf-,jk-,khsf-,bl=6,xxcc=9,dxtvkd=8,zsg-,nnkl=8,kglvq-,rzpt-,nfv=4,xvh-,hz=4,nsm=6,gm=2,cp-,qndj=4,vhzd=9,hmv=5,zfhmj-,rtclsf=4,hgv-,jk-,tbc=4,jfrkh=2,pf-,tch-,zxz-,mf-,zsgl-,pgpzq-,hhz-,nk=3,gpt=4,zxz=4,jpn-,tqb-,htn=2,nks=3,vd=7,gtx=1,rd-,gzx=6,gnvcc=8,ts=8,ckrt-,jdb-,kk=3,gq=7,nbd=5,msb-,hzq-,pfsff-,jq=5,ngs-,dj-,vmcsh=3,nsm-,kpmfqs-,pmp-,vsd-,jgs-,slds-,lzmb=4,njv=9,bclt=5,gnhjs=5,xj=5,bqblll=2,ddn=8,mhx=5,tjfk-,jb=3,msb-,ckcslv-,njv=2,htn=1,zs=5,stg=2,knp-,nsnn=7,mz=4,hjp=5,vjl-,jzhvv=5,zzqmg-,mjx=2,xpl-,xlkb=7,fhp-,vjl-,hqlkpl-,nt=6,zj-,bzk=5,tg=3,sgv-,lrkmv-,pz=9,xg=5,hgv-,szxdt-,gcc-,qgp-,qnn-,zdks-,nn-,sspm-,tt-,mdvnr-,pgpzq=1,rbt-,nn-,bltn=7,msl-,szxdt-,tl-,hjx-,cxxrc=3,shx=1,qq-,mcl=3,qndj=4,cx-,nks=4,chfsm=9,vsd=8,cf-,kvkdr-,pt=8,gfjht=4,mth=5,pxlvz=2,tv-,ttk-,sj=6,kzzn-,vsd=4,hmv=6,zdtb=5,jc=5,dsfb=6,ckrt=3,gg-,tsvtm=8,hb-,tb=7,mnpbcf-,krl-,kphb=3,tcqz=5,cpz-,ggf=9,ljr=8,rzgg-,ssp-,hbg=5,lzmb=3,psf-,knp=1,dj-,ljr=5,rl=2,cpb=6,tv-,kpv-,jb-,gk=7,mcpkb-,mcpkb-,xsbg-,gq=7,mcpkb-,bpf=1,lmpxsn=5,ckrt-,vm-,td=5,pxlvz-,lrpxp=7,ph=6,gp-,hdn-,svg-,htn=2,bzp-,dbs-,hhz-,dgk=5,sjdkl-,rf=5,zjhht-,mch=9,xgrs=4,cmp-,rzpt-,mdn-,jknn=5,mdvnr-,tsvtm=6,gdx-,tq-,dvh=1,xpl=6,gxd-,rqzxz-,cx=8,pxlvz-,hc-,vgc=7,bbth=6,vsd-,glmzc=6,dxtvkd-,gc=5,bmxzp=7,mhqzc-,ddk=3,cc-,hmv-,vjl-,cf-,jc=1,mth-,xvfc-,qjz=6,vkf-,kpv-,xvh=3,pmp-,gm=9,fx=6,zj=1,rbt-,xsh-,zfhmj-,nkr=1,vmh=2,nsm=6,psf-,xgrs=3,bzsx-,srb=5,vkm=3,shx=1,zj-,cpz-,glmzc=7,jf-,vz=7,pb-,mbp-,mt=2,xb=4,jpb-,zs=1,mdvnr-,lpd-,mxtz=1,dgpf-,smnh=8,td-,zfhmj=7,lrpxp=2,rzpt-,sbvx=1,rtclsf-,px=7,bl=7,rf=1,bqctt-,qq-,hg=3,srb-,nmn=8,hr=3,qskn=4,vg=7,psb-,hg=7,mcl=2,pz-,bz-,mcl-,rnk-,hgv=8,sh-,pjct-,hvvh-,qqh=5,kb=7,vsd=8,mnx=4,lrc=9,htzgz=8,tb=4,tch-,thl-,hdn=6,dvd=1,gxmgld-,sf-,jk-,xsbg-,bmhs=7,dgk=7,kqql-,mz=6,mn-,zvg=9,xp-,fk-,rtclsf=5,tjfk-,gpjm-,kphb-,zv-,grkk=9,pzjgls=1,fn-,zjhht-,sgvz=4,ggf=6,zbc-,nptmr-,sbvx-,zzmxzs=2,dv-,xpl-,kbmc-,tn-,rzcx=7,vcp-,ps=5,lpd=4,dd=8,qg-,hd-,bj=8,qnn-,rqzxz=3,sspm=1,dnb=2,jf-,chfsm-,lh-,lzmb-,jx-,xzkj=5,lrdkf=3,mzfl=7,mxh=5,xxcc-,bjd-,ng-,vgdb-,vcp=1,qqj=9,gxc-,xp-,tb-,xp-,jk=4,rj=3,tbc=5,vmh-,zzx=8,tc=9,dgf-,ftp-,slds-,qbns=8,pssx=1,rd=8,zbc-,kglvq=5,nks=9,szdz-,bdlt=6,tm=7,psr=8,kp=7,rbt=9,kzt=8,gzx-,sdg-,pc=3,gxmgld=3,vmcsh-,dj-,kpv=2,lpd=5,hpmn-,nkccfg-,qbns-,jc-,mxh-,hgpd-,lcq=6,rqzxz=2,zk-,qjjfz-,fvpqcp=2,jpn-,mktfz-,vhzd-,dkv=2,px-,rzcx=3,dbs-,mlp-,mbrmr=5,hvvh=5,gdx=5,rxrt-,dvd-,sdbj=9,ncndp-,cb=1,xxcc-,hch=9,sn=5,pfxhxj=8,bfsnt=5,ltf-,qb=5,km=7,kd-,zzqmg=1,rlfgd-,kn-,hjx=9,jv=5,ntgd=3,rzcx-,mt=5,pzjgls-,rnk=9,stg-,tzz-,rv=1,qr=7,vcp=6,gdc=6,mnt=6,hch=4,mt-,rh-,zgs-,vnk=2,pb-,gxs=5,mn-,jnps-,px-,tzz-,jkz-,dsfb=8,pf-,cb=4,sx=8,lpd-,jhm=3,nnkl=6,sgv=8,xxcc=9,xjznm=9,vxr=1,xxcc=6,pjl-,chv-,zvg-,sqt-,vbs=2,pgpzq=9,nrvg=2,vgv-,lcm-,dj-,kq=1,mk=7,msl-,pgpzq-,mjx=7,kqql-,rbvl-,gxc-,xm-,qfpf-,nsnn-,gxd-,sx=7,nj=6,bclt-,sdg-,svg=2,ssp=4,gk-,scx=8,nsm=1,rvr=5,jkz=4,lcm-,pjl-,kr=1,gfjrh=6,dxtvkd-,qhsj=5,ckcslv=5,bnn-,hxl=8,rj-,kqql-,hp=8,nfv=7,vgdb=7,qb-,dcmx-,cf=4,nvx-,hh=5,hdn=5,bck-,chv-,xh=3,mdvnr=9,ztcgrm=2,vpnk-,jk=1,gnvcc-,ftlcft-,zj=2,tp-,crxg-,sft-,hp-,xv-,pjct=7,hb-,rlfgd=3,mt-,gbxh=1,vdfx-,xv=1,lbdrk-,xvh=6,jgs-,dbs=6,hhz=3,mcpkb-,qx-,sccd-,bjd=4,pz=5,xb-,mxh=8,vxlgph-,gnvcc=6,kbmc-,mn-,db-,mlp-,dnb=6,ps=8,ngqh-,vlnd=3,qndj-,nks=3,pjl-,vpnk-,dsp=9,tq=3,mdn-,jpb-,vhzd=3,kp=2,tm=1,lrdkf-,vg=4,mkn=4,xxcc-,lbdrk-,pc-,glmzc-,fqqx-,hmv=8,dk-,dkv-,dkv-,pb=6,vmcsh=5,pmp=8,khsf-,psb=5,jpb=8,pgpzq=5,scx=2,lh=1,tt-,pgp=4,dv=7,ss=5,rjrm-,sccd-,ph=2,dj=8,pdg-,rxrt-,mxtz=2,xj=9,jfrkh-,bt=9,bzk=3,ngs=8,gpt=6,fjrp-,kb=5,zzmxzs=7,px=5,nrvg=3,vcp=4,xqgl=5,qskn=3,mdvnr-,bg=5,rf-,pzjgls=5,rz=3,zsq-,vbjk=2,zsgl-,rh=5,zsq-,kgk=8,pdg=3,tt-,nmrt-,srb=5,dv=5,grkk-,sjdkl-,tjfk-,hmv-,kbqc=2,pfxhxj-,vbs=7,pgr-,jfrkh=1,qgt=4,kp-,jc=2,htn-,sspm-,nkr=4,cspg=2,tm-,mxtz-,qbns-,mxtz-,pgr=1,bclt-,xdk=1,clpc=1,gnvcc=9,lpd=1,tc-,sh=2,rzxt-,ts=6,rnk-,cmp=6,vl=2,psr=7,zzmxzs=7,td=8,snz-,kjcqvr=1,vhzd=6,fr-,htzgz=8,xv-,kpd-,rbt-,rvr-,jsz-,vss=3,xv-,sq=6,scx-,fjrp-,gxd-,js-,nkr-,cc-,mhqzc-,vv-,xdk=7,bck-,qh-,sq-,ckrt-,fkrs=2,zf-,prf=3,tjfk=5,sgv-,lk-,rqzxz=7,rvs=6,dsfb-,rvs=9,htn-,cpz=4,gtx-,jpb-,qbpq=7,hd-,cpz=6,mkn=2,bt=5,hp=7,gbxh=3,prf-,xp=3,lls-,qjjfz-,mnpbcf-,sx=4,mz=9,pzjgls-,szdz-,zzqmg-,mzfl=8,kpd=6,cqs-,zsg=2,qqj-,vhzd=7,qx=1,pxlvz-,mq=1,gk=7,lzmb=2,jbgf-,dcmx-,xzkj-,tg=8,fr-,mkn=1,tn=9,klnvl-,vmm-,zgs-,rj=3,zzmxzs=5,fpp-,stg=2,gk=9,cfx=7,bpf-,xkt=1,lrkmv=1,sgvz-,sdg-,rxq=3,lcq-,zsq-,smks-,ctg-,xqgl-,bb-,glmzc-,sdbj=9,rncmzp=8,ljr-,kz=6,bltn-,tjfk-,vcp=7,fk=1,fhp-,mcpkb=2,dsfb=3,vkm=9,thn-,tsvtm-,cf=2,flp-,rd=4,gc-,mdn-,zvg-,dgf=4,lqq=7,tcn=5,vgv-,rncmzp-,pjl-,sjdkl=3,rtclsf-,slds=7,pb=1,xvs-,vcp-,zsg=9,vsd=4,kgk-,lh-,mktfz-,bltn-,gdx=5,hzq=7,cpz=7,vld=1,nt-,cqs-,hl-,pzjgls-,cqs-,xg=3,ng-,dg-,nkzzc=1,hc=8,ggf-,zc=8,glmzc-,krdk-,cb-,vzp=2,mv=6,cspg=4,pb-,vmm-,sck-,vvl=9,qnn-,htn-,nt-,xqgl-,nvx-,qskn=8,vkf-,dvh=9,xc-,vh-,jq=2,zsq=1,jgrd-,kbmc-,mz-,dnb=5,njv-,mxh=3,bmhs-,jhm=7,ghk-,rnk-,tch-,xfg-,rxrt=7,tbc-,dg-,mhx=8,sh-,pz-,mnt=4,sbx-,mz=6,rv=5,gpt=8,nmrt-,bmxzp-,jv-,krdk-,tqhs-,gfjht-,sccd-,clpc-,xsbg-,jpn=9,szx=4,mhx-,mt=4,zvg=9,szx-,ng=4,mjx-,qg-,zzqmg=7,xb-,gr-,xm-,xxcc=8,mq-,hg=1,vz-,bqctt=6,rbvl-,gqgzxf=3,mk=6,thn-,mnt=4,mcpkb=7,knp=2,snz-,jzhvv=2,ndq=9,mq-,mkn-,mf-,ss=4,zbc=7,zzmxzs=1,pgr-,njv-,qb-,bfsnt=4,bnn-,hmv-,zbc-,ckrt=5,bpf-,vht-,sbg=7,vmcsh-,rbpp-,qgt-,lcm=9,rbpp-,bl=1,sck-,vsm-,rf-,krdk=4,mjx=6,pfsff=6,tg-,sn=7,qbns=2,vzp-,qx-,chv=1,qr=3,ch-,khsf-,sgv=9,qjz=1,smks-,rqzxz=7,cb-,nnkl-,kzzn=1,vphf=3,nt-,hxl=8,sh=2,rtclsf-,scx=7,kb-,mzfl-,zzmxzs=7,ssp=4,nptmr-,xlkb=4,jbgf=1,kf=3,tv-,zsgl-,xsh-,kq-,mch-,hb=5,vss=7,bg=9,msb-,fr-,pz-,zgs=6,ngs-,jdb=9,hjx-,dcmx-,rt=9,rbt-,vc-,tt-,qjjfz-,flp=5,hg-,xgrs=7,psf=1,vtms-,mkn-,mcpkb=1,tls=6,fqqx-,zgs=9,ckcslv-,kglvq-,dvh=3,sqt-,hhz=6,mnx=8,msl-,kzzn=2,flp-,hr-,jhm=6,qgp-,lqq=7,hpmn-,gzx=6,vdfx-,tm-,rfs=1,zc-,flh=1,lmhb=7,jf=1,vcp=7,vmh-,kr=9,hxl-,xlx-,vtms=5,px-,fjrp=8,lqq-,nfv-,vdl=8,tm-,vsd-,kb-,hp=8,ctg=9,hqlkpl-,fkrs=4,jvx-,hdn=8,zzqmg-,gzx-,kzt=9,dd-,ddn=5,sbg-,fqlnbc=7,shx-,fhp=4,ch=1,pnq-,nbd=2,xv=5,qbpq=6,jk=7,cc=4,mhqzc-,xfg=3,lvfdjv-,vv-,hjx=9,lkks-,pnq-,ngs-,nbd=5,td=5,flh=6,zbk=5,smnh-,rv=9,vv-,kg=1,jvx-,lf=2,gg=7,tqhs-,kpmfqs=1,xjznm=6,tb=7,zjhht=6,pssx-,zdjgj=6,rlfgd=6,mbrmr=8,dv-,psf-,sn-,qbpq=2,bqblll=6,xh=5,tqhs=8,gxc-,rzcx-,vp-,zc=4,fvpqcp-,kd-,pc=7,dbs=7,zbk-,pm-,cspg=7,qfpf-,hr-,dhjv=3,tbc-,tn-,sdbj=5,pxhnxj-,nsnn-,nmrt=1,sck-,zg=4,bdlt-,bc-,rncmzp-,khsf-,krdk-,lk=2,kjcqvr-,vkm=1,vtms-,nsm-,slds-,lcm-,kqql=3,mktfz-,shx-,xsh-,lh-,rl-,cc=5,pgpzq-,gdx-,vnz=5,bltn-,gtm-,vtms-,rh-,hjx=8,zc-,mzfl=2,vsm=7,pnq=5,rxq-,gcc-,zdks-,nn-,ngqh=1,clpc-,pxhnxj=2,hvs=6,dj-,pssx=7,jvx=1,zs=6,gk-,mnx-,jpb-,jxf-,jpb=4,pxhnxj=1,gp-,vht-,dnb=7,kd=9,pl-,kb=7,nt-,hmv=6,sx-,hxl=9,nmn=8,kq=9,df-,cxxrc=3,xvs=8,kphb=6,xlkb=5,lrkmv-,rjk=7,zf=1,scx=4,rfs-,ckrt=2,hgv-,qqj=5,lcm=7,hgpd=3,hjp=6,hzq=4,qjjfz=1,nmq-,thn-,ghk-,bk=4,kpv=9,xgrs-,dbs-,rxq=8,fpp=8,lpd=6,nmq=6,th=6,nk=6,sdbj=2,kr-,zg-,gnvcc-,hg=1,sh=8,nmq-,jzhvv-,ggf-,kgk-,kvkdr=7,xznvs=6,fr=9,tjfk-,rxrt-,sspm-,hdn-,xh-,grfm=2,mdvnr-,rh-,vh=2,nkccfg-,xlx-,dj-,vtms=3,gtm=6,vxlgph=9,rbvl-,lpd-,vmh-,tch=7,ckrt-,tqb-,dkv-,rfs-,pssx-,kglvq=6,jvx-,hz-,rt-,hg-,jk=7,kr-,bg=3,tch-,df-,cspg=4,qgp-,vc-,dgpf-,ff=2,hmv=8,jsz=5,hg-,zvg=7,cx-,gfjrh=3,xfg=2,jc=5,xzkj=4,xb=9,zbc=4,zdtb=5,jnps-,jxf-,nkr-,xdk=7,hpmn-,kpd=5,zk=5,gc-,dcmx=5,ngqh=8,rtclsf=1,gdx=3,hc=3,vphf-,mf-,vmcsh-,dj=9,bz-,zzx=7,kn=8,pvdzq=4,tch=1,tch=7,fv-,bk=5,kjcqvr=1,hgqr-,ddn-,bbth-,dj-,bclt=9,cxz-,pbdd=7,xxfrf=6,ltf-,nj-,zsgl=2,fqqx-,gr=4,hp=7,gdx-,msb-,vc=1,ml=9,lmpxsn=7,lpd-,fbng=3,mth=7,pbdd=5,fhp-,lkks-,zhd-,ltf=6,khsf=4,qr-,mcl=4,hhz=8,kbqc=3,vgc=6,px=7,stg-,fvpqcp=8,vdfx-,js-,hz=8,qndj=6,nsm=9,sx=4,ghk=2,xp=1,pfsff-,kd=5,rzpt=4,dhjv=2,xv-,mnpbcf=5,cc=9,xzkj-,pzjgls-,flp=4,ftlcft=4,hjx=6,rt-,dv=8,vtms-,xp-,hgjhv=6,ps-,rt-,kzt-,kg=7,sf-,dhjv=3,qb-,mbp-,fv=1,xh-,vdfx=8,scx-,dsfb=3,rnk=5,kp-,sgv=4,tbc=9,gpt-,cqs-,dnj=1,fk=2,mch-,tbc-,gxs=4,hqlkpl-,crxg-,qhsj-,clpc-,nptmr=7,krdk=2,rbvl-,ckrt-,zdjgj=4,smnh=5,fk-,hjp=9,jxf-,kpb-,ljr=6,jv-,msb-,xg=9,hb=6,tl=3,stg-,qbpq-,vgv=3,tl-,mkn=2,rvs=6,ngqh=8,bg-,crxg=2,gc=3,lh-,qqh=5,xzkj=1,zj-,mv=5,sdbj=5,jx=6,vm=6,jgrd-,rjrm-,jsz=8,th=8,njv-,dcmx=3,rd=5,rzpt-,mn=5,vtms-,zdks-,mktfz-,kf=1,mdn-,ff=8,fk-,dgpf=9,xdk=6,nnkl=4,xzf=4,kk=2,mcpkb=2,bck=8,vpnk=9,xznvs=2,lk=2,ltf-,tc-,nmn-,zs-,tl=2,vzp=4,szx=3,lmhb=7,psb=8,ps=4,jv-,qgt-,nk-,nk-,ssp=3,rf-,pxhnxj-,pfxhxj-,qgt=4,gnvcc-,sgvz=3,pt-,rv-,sf=6,vgdb-,bbth-,gr=7,kbmc-,nrvg-,cspg=9,kg=9,dvh-,lh=9,vnk=5,pvdzq=3,kn=8,mdn=8,nmq-,rq=4,kp=4,gfjht-,ckcslv-,fkrs=4,nks-,xqgl-,hc=8,ssp-,fz=1,ssp=7,ps=2,kphb=9,nsm-,stg=7,bmhs-,sck=1,xj-,cmp-,ghk-,nn-,zsgl-,qbns-,rtclsf=9,zhd-,lrc-,gdc=3,mch-,sjdkl-,bmxzp-,lvfdjv-,vg-,qgt-,cfx-,ph=3,xsbg-,hr-,dkv-,cc-,nptmr=2,nfv=7,sccd=8,hjp=6,dxtvkd=2,hz-,vkm-,xxcc-,hpmn-,sqt=9,qx-,bj-,vnk=2,lrc=6,hmv=4,hbg=4,kbqc=8,zxz=1,qg=9,dg-,kz-,bzk-,xzf-,hg=6,mch=5,dbs-,qx-,qgt=5,bqblll-,tl-,qx=2,nmq=3,mlp=1,hzq-,bnn-,vmm=1,ljr=9,tp-,qg-,jvx-,vtms=6,ltf=1,rbpp-,flp=6,gtx=4,gr-,pgpzq=2,nks=2,px-,rv-,hgjhv=6,dv=8,lmhb-,ch=3,htzgz-,sspm=3,jknn-,ndq=3,qbpq=7,dgpf=5,qndj-,ctg=4,kn-,cxz=8,lrkmv=5,krdk=6,gtx=8,hch=9,nkzzc-,cqs-,kg=4,zzmxzs-,jx-,gfjrh-,vld-,qpcvg-,hgv=4,dkv-,rxrt=2,vmm=5,mnx=7,kd-,dhjv=3,nks-,rp-,svg=4,glmzc-,lls=9,bqblll=9,qpn=8,qskn-,rbvl=6,vm-,mk=3,cspg=5,slds-,cl=6,xg-,xc-,rncmzp=4,pzjgls-,hd-,hvvh-,xkt=2,smnh=4,tm=4,lnc=4,gtm=1,snz-,rqzxz-,ssp-,xg=2,zv=7,pjct=6,mq-,bnn-,sx-,xfg=9,ljr-,bj=8,pbdd=8,ttk=7,cx=1,snz=6,dkv-,tv-,pxhnxj-,jpn-,jgs-,mxh=1,mf=7,kq-,hz-,vz=8,bzsx=4,jnps=1,dgf=8,zgs-,fbng=4,mk-,pt=7,nmq-,ngs=8,lh-,vkm=6,kqql-,vg=2,gg-,cxz=8,hr=4,tq-,gxs=6,cspg-,mth=9,xjznm=6,bzsx-,pzjgls=9,krdk=6,jxf=9,mdqh=5,ssp=6,njv-,mch=1,gqgzxf-,sgvz-,pssx-,zsq=7,ng=6,rzcx-,sdbj=1,zsgl=1,szx-,nrvg=1,dtdk=9,dbs-,kqql-,hjp=5,ddn=2,df=8,zg-,xfg=7,cx-,nmq=9,bzsx-,sft-,gfjht=2,bqctt-,gtm-,sqt=8,ljr-,shx-,gcc=3,kjcqvr=5,tt-,xvfc-,ghk-,tls-,hb=5,pz-,vphf=1,rv=6,zf=9,vzp=9,ml-,thl-,kbqc-,knb=4,tsvtm-,bzp-,pnq=2,scx=6,nt-,ngs=4,vpnk=5,pb-,lrdkf=6,jfrkh=8,crxg=8,gpt=6,bmhs-,vss=2,pgr=9,mhqzc=8,jgrd-,bz=2,kqql=9,gxmgld-,pl=8,dd-,hgqr=3,tcqz=9,zk-,zhd=3,pgp-,th-,vxlgph=9,gxmgld=5,gpjm-,cfx-,bbk=5,ltf=1,pgr=7,tjfk=3,vkf-,nfv=2,zdjgj-,knp-,bck-,vb=9,hd=5,sdg=6,vgv-,th=3,fqqx=8,gxs-,dcmx-,zs=4,fzs-,zsgl=9,nbd=1,fv-,lrdkf=6,vjv-,sck=1,qx=8,jdb-,zdjgj=5,sbg-,pgp-,kzt-,zg=4,pgpzq-,rtclsf-,bpf=6,dnb-,kzzn=4,cp=1,td=4,jpb-,xqgl-,lrpxp=7,xh-,tt=4,xgrs=3,vkm=9,xpl=6,nkccfg=8,sn=1,bl-,ssj=2,snz=5,dgk-,tch-,bmhs=5,mbp-,gtm=4,dg-,slds=5,gtx=5,xr=4,msb=2,ftp=5,tch=8,vl-,mdvnr=6,dk-,sgvz=4,fz-,rzpt-,sspm-,gr=6,nl=3,hp=9,pzjgls-,vdfx-,nj-,xxcc=5,db-,bjd=6,ps-,gtm-,psf-,ncndp-,nt-,mnx-,tc-,lkks=9,mn=7,rvs-,cpz-,vpnk=1,ks=8,vht-,nmn-,vpnk-,vxlgph-,xm=2,qg-,jv=8,sck=9,gpt-,rbt=2,mdn-,gxc-,bzsx=7,tm=5,lh-,nn=1,th=9,ckcslv=5,hvs=1,sccd-,mcpkb=4,vcp=6,vz-,rjk-,mcpkb=2,gcc-,jdb=4,bz-,kq=8,pnq-,ntgd=9,ss=6,pl-,szx-,lkks-,pmp-,lf-,ghk=7,ckcslv-,kz=5,hdn-,vxlgph=3,qqj-,gpjm=1,vmcsh=8,krdk-,mch=2,kpd=8,gdc=4,fz=4,fl=2,gc=2,mbp=3,kczrf=8,fk=2,gr-,fkrs-,dnb-,zs=7,xzf-,lnc-,xznvs-,rzgg-,xpl=5,dk=4,jk=9,mjx=6,kphb-,cpz-,lmhb-,fz=6,sgv-,zzmxzs-,cp=3,zzx=9,hb=7,nkzzc=2,kphb=9,nsnn-,jfsg-,pzjgls=7,fpp-,gqgzxf=4,tb=9,rz-,sqt=2,lqq=5,xvfc=2,mbp-,rp=8,zxz-,qg-,jknn=3,nks=2,dgk-,cf=8,gxc-,gq-,crxg-,qx=9,sbg-,vss=7,xt-,kqql-,khsf=1,dvd-,zc=6,vzp-,jvjdbb=9,kq=7,zdtb=1,slds-,msb=7,jfrkh-,vss-,xp=6,fvpqcp=6,bclt-,th=6,kpmfqs=5,sdbj=8,mth=2,cfx=5,kz-,kpmfqs=5,pgr=8,vm=8,bb-,sh-,bk=4,zzx=5,jpn=3,pgr-,pjl-,kqql=5,hhz=4,vnk-,mxh=6,zbc=7,dvd-,qpcvg=4,lpd-,hd-,gr=2,mq=3,nkccfg-,rzcx=8,sgvz=3,nks=3,qqj-,gxmgld=7,th=4,pjl=2,xvh-,df-,hl=3,zjhht=5,zgs=2,kp=4,rtclsf-,xvs-,bbth=3,pdg-,nmrt=9,smnh=3,vsd-,fkrs-,pf-,sbg=9,jfsg-,vcp=6,jb-,xzf=3,xvfc=8,kq=3,zbc-,hpmn-,rzcx-,tbc=3,zsgl-,lqq-,hzq=4,vdl=9,hd=1,mq-,prf-,qqh=2,lrdkf=5,vmcsh-,rjk-,pbdd-,sx-,jk=7,bmxzp=9,tq-,pgpzq-,jzhvv=9,fv=6,ks-,rf=7,bl=7,pdg-,pzjgls=7,mxtz-,hgpd=2,hb=2,rzcx-,vmcsh-,gxc-,kpmfqs-,mch=4,zzqmg=4,kczrf-,hz-,vhzd-,hzq=7,qhsj=5,mn=8,bzk=3,vgdb=8,vdfx-,nkccfg-,xzkj-,tv-,pssx-,gm=2,lbdrk=2,xvs=8,hb-,dnc-,mdvnr=2,lrpxp=1,hxl-,dgk-,ps-,vvl=1,xv-,vb=8,mch=4,rtclsf=9,rxq=6,hgpd-,zv=2,qnn=1,fkrs-,knb-,gm-,kczrf=5,gxmgld-,vxr=8,vgdb=3,pbdd=5,pssx-,zq=1,nfv=5,pxhnxj=8,hbg-,ngs=9,kglvq-,bg-,gk=2,cb=2,cxz-,vxlgph-,ml=3,lrc-,bfsnt=7,nk-,pb-,vp=2,vgv=7,flh-,pgpzq=3,rz-,xxfrf=2,hz=4,htn=5,sck=2,vhzd-,vc-,rq=4,vpnk-,mn=4,rzxt=2,hgpd-,lqq-,ssp-,kbmc=4,bz=3,rt-,shx-,pm=8,qhsj-,xb=2,hbg=9,kqql=4,mnpbcf-,kn-,ndq-,hvs=4,dgf=5,tqb=9,xvs=7,smnh-,htqt-,xvs=5,xvfc-,glmzc=9,gxd=2,fn-,jpb=5,jvx=3,vjl-,gq-,xxcc-,zhd-,zhd-,jhm-,ckrt-,vm-,vjl-,zj-,ftp-,xv-,dgpf=8,ttk-,nptmr-,zgs=3,tt-,vgc-,hb-,knb-,kpmfqs-,mlp=6,vgdb=5,hqlkpl-,tc-,fr=1,ljr-,ttk=4,xxcc=7,xt=9,rmm=9,fv=8,dhjv-,dgk-,tzz-,kczrf=9,kg-,jkz=6,xpl=9,ml-,qbns-,ttk-,mbp-,ddn=5,vhzd=8,kglvq=7,bpf-,crxg=9,vvl-,lnc-,jk-,xgrs-,gpjm-,hh-,zbc=3,ckcslv-,snz-,xpl-,fk=2,tjfk-,dbs-,mv-,ff-,pvdzq=1,nn-,kz=3,hgjhv-,km=8,rq=5,zgs-,lrdkf=8,krdk-,jhm=9,nks=9,szxdt-,knb=7,xsbg=6,dnj-,psr=5,lmpxsn-,bqblll=7,dnc=5,bdlt=3,tv=8,knp=1,mktfz-,vmcsh=2,hjx=1,gtm=3,xlx-,zsg=6,sqt=7,fk-,bc-,kq-,rxq-,jgs=2,lmpxsn-,ddn=9,sgv-,szxdt=2,cp=4,tp=5,xzf-,zhd=1,mfx=1,xg=4,fn=3,rjrm-,lrc=8,vg-,sgvz-,jf=5,qg-,fx-,msl=4,pl-,nk=6,jsz-,msb-,vg-,ngs-,szx=6,hjp-,vv=6,qjjfz-,sgvz-,tl=8,mxh-,xvfc-,ssp-,tqb=7,fn=5,gk-,nmn-,msb=2,ftlcft-,mfx=3,mjx-,lls=1,fqlnbc-,hc-,sf-,db-,gtx-,vc-,xznvs=6,hl-,vss=1,sft-,sspm-,sft=8,gtm-,gxc=2,tbc-,cfx-,lpd-,psb-,sft=9,kgk-,mn-,zvg=2,qgp-,vg-,bfsnt-,hvs=7,pjl-,njv=5,qbns-,qpcvg=9,rfs=9,bbk=3,qg-,tqhs=3,xsbg-,zfhmj=6,zsq-,hhz=3,mbrmr-,pbdd-,qb-,fhp=3,mbp=9,ch-,bg-,rz=7,rl-,qs=3,sjdkl-,xt=3,cp-,zsgl-,pdg-,bpf=6,krl=5,sck-,dg=4,hb=4,rncmzp=7,kbqc=8,nsm-,nfv-,bclt=4,hmv-,rt-,pvdzq=9,nnkl=2,dgk-,dgf-,vsd=7,kz=4,klnvl=6,rzcx-,mnx-,kpb=3,jq=6,db-,fx-,zjjmb-,jc=4,kzzn=3,vphf-,lh=9,mnpbcf-,hqlkpl-,szdz=5,xzf=8,rj=1,nnkl=9,qfpf-,xh=3,js=5,ggf=8,zdjgj-,zsgl-,zq-,psb-,cmp=5,glmzc-,gpjm=5,chfsm=5,lnc-,srb=1,xvs-,snz-,rncmzp=9,xsbg=4,pt-,smks=3,ljr-,ckcslv-,mfx-,mktfz-,mn=1,zhd-,nnkl=9,mzfl-,km=3,grkk-,crxg-,qrr=1,thn=1,hd-,gfjht-,xsh-,xdk=9,xzf=7,ks=1,kk=7,dsfb=2,hjx-,pgp-,qgp=5,qpcvg=4,xv=4,xxfrf-,pl=4,smks-,pt-,msb=4,bclt-,qndj-,jc-,ts=5,gbxh-,dhjv=1,sgvz-,mjx-,jkz=6,sf-,sjdkl=9,crxg-,zg=9,zjjmb=2,zc-,hxl-,mn=9,dvd-,vnk-,nbd=7,gbxh-,ljr-,hh-,kn=3,fn=1,xqgl-,ng=1,sx-,lrdkf=4,dg=9,ngqh=5,gxmgld-,hch-,qpn-,gcc-,zjhht-,df=8,rp-,rv=6,mktfz-,kr=9,bzk-,lpd-)"sv;

} // namespace day15
