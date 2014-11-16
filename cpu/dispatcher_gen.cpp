switch(opcode_1) {
case 0x00:
	add_Eb_Gb();
	break;
case 0x01:
	add_Ev_Gv();
	break;
case 0x02:
	add_Gb_Eb();
	break;
case 0x03:
	add_Gv_Ev();
	break;
case 0x04:
	add_AL_Ib();
	break;
case 0x05:
	add_rAX_Iz();
	break;
case 0x88:
	mov_Eb_Gb();
	break;
case 0x89:
	mov_Ev_Gv();
	break;
case 0x8a:
	mov_Gb_Eb();
	break;
case 0x8b:
	mov_Gv_Ev();
	break;
case 0xa0:
	mov_AL_Ov();
	break;
case 0xa1:
	mov_rAX_Ov();
	break;
case 0xa2:
	mov_Ov_AL();
	break;
case 0xa3:
	mov_Ov_rAX();
	break;
case 0x28:
	sub_Eb_Gb();
	break;
case 0x29:
	sub_Ev_Gv();
	break;
case 0x2a:
	sub_Gb_Eb();
	break;
case 0x2b:
	sub_Gv_Ev();
	break;
case 0x2c:
	sub_AL_Ib();
	break;
case 0x2d:
	sub_rAX_Iz();
	break;
case 0xb0:
	mov_AL_Ib();
	break;
case 0xb1:
	mov_CL_Ib();
	break;
case 0xb2:
	mov_DL_Ib();
	break;
case 0xb3:
	mov_BL_Ib();
	break;
case 0xb4:
	mov_AH_Ib();
	break;
case 0xb5:
	mov_CH_Ib();
	break;
case 0xb6:
	mov_DH_Ib();
	break;
case 0xb7:
	mov_BH_Ib();
	break;
case 0xb8:
	mov_rAX_Iv();
	break;
case 0xb9:
	mov_rCX_Iv();
	break;
case 0xba:
	mov_rDX_Iv();
	break;
case 0xbb:
	mov_rBX_Iv();
	break;
case 0xbc:
	mov_rSP_Iv();
	break;
case 0xbd:
	mov_rBP_Iv();
	break;
case 0xbe:
	mov_rSI_Iv();
	break;
case 0xbf:
	mov_rDI_Iv();
	break;
default:
	assert(false);
}
