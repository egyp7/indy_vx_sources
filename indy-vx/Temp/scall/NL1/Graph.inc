; o GCBE
; o U/K, MI
; o (c) Indy, 2011.
;
; �������� ������ ���� ����� ������� ������ ���������
; �, ������� ����������� � ������ ��������������� � �
; � �������� �����������. �������� ���� ����������� �
; ���� ������ �������(�� ��������� ������ ����������).
; ������� ��������� �������� ��������� ��� ������� ��
; ������� ����� � ���������. �������, ��� ��������� � 
; ��� � ���� � ���������� ��������� �� ������� 4-� ��
; ��. ����� ������� ������� ��� ���� ������ �� ������
; ��� �������� � ������������ ��� �����.

TYPE_MASK			equ 11B

; [����� �������� ����� � ���������� ���������� � ���
; ����� Eh(Entry Header). ������ ������������ ������
; ���� ��������������� ����� �� ���� � ���������.]
; �������� ������ 4-� ����� ���� ���������� ���������.

; o ��� ��������� ������� ���������� ����������� ��������� CX_REPLACE_GRAPH_LENGTH.
; o � ������ ������ � ������� ����������� ������ ���� Address ����� ��������� ����� 
;   ���������� � ���������� ������, ����� ������������ ���������� ��������� � ��������� 
;   �����, ��� ������� ������������ ��������.
; o ���� ���� �� ��������(����� ����� ����������� � ������ �������� ��), �� ������ ���� 
;   �������������� � �������� ����������� GP_MERGE.

; ��������� ��������� �����.
BLOCK_ENTRY struct
Link			LIST_ENTRY <>	; Link.Flink & ENTRY_TYPE_MASK = ENTRY_TYPE_LINE
; Flink:
; > 00 Line
;   01 Subroutine
;   10 Branch
;   11 Conditional branch
; Blink:
; - �����(GCBE_PARSE_SEPARATE).
;   XN
; - ��� ������������� ����(ACCESSED_MASK_FLAG).
;   NX
Address		PVOID ?
UserData		PVOID ?
_Size		ULONG ?	; ������ �����(����� ���� ���� ���������� �������� � ����������� ����).
IpCount		ULONG ?	; ����� ���������� � �����.
IpLength		BYTE ?
KitFlags		BYTE 3 DUP (?)
CrossLink		PVOID ?	; ����������� ������ ����� ��������� Rw' � Cs'.
BLOCK_ENTRY ends
PBLOCK_ENTRY typedef ptr BLOCK_ENTRY

; ���� ���������� ��� ���� ��������� ��������� �������� ����������.
EhSepatateFlag		equ BLOCK_ENTRY.Link.Blink
SEPARATE_MACRO_FLAG	equ 01B

EhSize			equ BLOCK_ENTRY._Size

; ����� ����������(LDE(Ip)).

EhIpLength	equ BLOCK_ENTRY.IpLength

; ��������� ���� ����� ����� ���������� ������, ��� 
; ��������� �������� ��.

ENTRY_SIZE	equ sizeof(BLOCK_ENTRY)

; ��� ��������� ������� ����� ����� � ������������ ��
; ��� ������������ ������.

EhFlink			equ BLOCK_ENTRY.Link.Flink
EhBlink			equ BLOCK_ENTRY.Link.Blink

; ������ ��� ���� ����������(Link) - ��� ������, �� �
; �������� � ���������� ���������. ������� ��� ���� �
; ����� �� ��������� ���������(Link.Flink) ���������� 
; ��� ���������.

EhEntryType		equ BLOCK_ENTRY.Link.Flink	; TYPE_MASK

; ����� ������������ 4 ����:

ENTRY_TYPE_LINE	equ 00B	; �������� ����.
ENTRY_TYPE_CALL	equ 01B	; ����������� ���������.
ENTRY_TYPE_JMP		equ 10B	; ����������� ���������.
ENTRY_TYPE_JCC		equ 11B	; �������� ���������.

; ���������� Loop, Loope, Loopne � Jcxz �������� ��������� �����������(ENTRY_TYPE_JCC).

; ������ ���� ����������(Address) �������� ��������� �� ����������� ����������.
; ���� ��� ���� ��������, �� ���������������(�� ��������� ���, ����. ���������).

EhAddress			equ BLOCK_ENTRY.Address

; ��� 1 ���� Link.Blink �� ���� ���������� ������� � 
; ������������ ��� ����������� ������� ���������. (��
; ���������� ���������� �������� ����� ���� ��� �����
; � �������, ������� ��� ����� ��������� ������� ����
; �������).

EhAccessFlag		equ BLOCK_ENTRY.Link.Blink	; ACCESSED_MASK_FLAG
ACCESSED_MASK_FLAG	equ 10B	; _ENTRY.Link.Blink

; 4-� ���� ���������� ������� � ������������ ��� ����
; ���� ���������������� ������, ��������� � ���������
; �. ������������ ��� �������� ������� ����������� �
; �����.

EhUserData		equ BLOCK_ENTRY.UserData

; ����� ���������� � �������� �����.
EhIpCount			equ BLOCK_ENTRY.IpCount

; ��������� ������������ ���������.
CALL_ENTRY struct
Link			LIST_ENTRY <>	; ..ENTRY_TYPE_CALL
; Flink:
;   00 Line
; > 01 Subroutine
;   10 Branch
;   11 Conditional branch
; Blink:
;   X0 ����� ��������� �� ��������(Call Eax, etc.)
;   X1 ����� ��������� ��������.
; - ��� ������������� ����(ACCESSED_MASK_FLAG).
;   NX
Address		PVOID ?
UserData		PVOID ?
BranchAddress	PVOID ?
BranchLink	PVOID ?
;   X0 ��������� ��������.
;   X1 ��������� ��������.
IpLength		BYTE ?
KitFlags		BYTE 3 DUP (?)
CrossLink		PVOID ?
CALL_ENTRY ends
PCALL_ENTRY typedef ptr CALL_ENTRY

DISCLOSURE_CALL_FLAG	equ 01B
EhDisclosureFlag		equ CALL_ENTRY.BranchLink	; DISCLOSURE_CALL_FLAG

; ��������� ������������ ���������.	
JMP_ENTRY struct
Link			LIST_ENTRY <>	; ..ENTRY_TYPE_JMP
; Flink:
;   00 Line
;   01 Subroutine
; > 10 Branch
;   11 Conditional branch
; Blink:
;   X0 ����� ��������� �� ��������(Jmp Eax, etc.)
;   X1 ����� ��������� ��������.
; - ��� ������������� ����(ACCESSED_MASK_FLAG).
;   NX
Address		PVOID ?
UserData		PVOID ?
BranchAddress	PVOID ?	; ����� ���� ���������� ���������.
BranchLink	PVOID ?	; ��������� ���������� �� ������, �� ������� ���������� ���������.
; - ��� ���������(���������� �����������).
;   X0 Short
;   X1 Near
; - �������� ���������(��������� � �������� �������������).
;   NX
IpLength		BYTE ?
KitFlags		BYTE 3 DUP (?)
CrossLink		PVOID ?
JMP_ENTRY ends
PJMP_ENTRY typedef ptr JMP_ENTRY

EhBranchAddress	equ JMP_ENTRY.BranchAddress
EhBranchLink		equ JMP_ENTRY.BranchLink

BRANCH_SIZE_MASK	equ 01H	; BRANCH_ENTRY.BranchLink
EhBranchSize		equ JMP_ENTRY.BranchLink	; BRANCH_SIZE_MASK
; 0 - short, 1 - near.

; ���������� ���� ������������ ���������.
BRANCH_IDLE_FLAG	equ 10B	; BRANCH_ENTRY.BranchLink
EhIdleBranch		equ JMP_ENTRY.BranchLink	; BRANCH_IDLE_FLAG

BRANCH_DEFINED_FLAG	equ 01B	; BRANCH_ENTRY.Link.Blink
EhBranchType		equ JMP_ENTRY.Link.Blink	; BRANCH_DEFINED_FLAG

; ��������� ��������� ���������(Jcc, Loop, Loope, Loopne � Jcxz).	
JCC_ENTRY struct
Link			LIST_ENTRY <>	; ..ENTRY_TYPE_JCC
; Flink:
;   00 Line
;   01 Subroutine
;   10 Branch
; > 11 Conditional branch
; Blink:
;   X0 Jcc.
;   X1 Loop, Loope, Loopne � Jcxz.
; - ��� ������������� ����(ACCESSED_MASK_FLAG).
;   NX
Address		PVOID ?
UserData		PVOID ?
BranchAddress	PVOID ?	; ����� ���� ���������� ���������.
BranchLink	PVOID ?	; ��������� ���������� �� ������, �� ������� ���������� ���������.
; - ��� ���������.
;   X0 Short
;   X1 Near
; - �������� ���������.
;   NX
IpLength		BYTE ?
KitFlags		BYTE 3 DUP (?)
CrossLink		PVOID ?
JCC_ENTRY ends
PJCC_ENTRY typedef ptr JCC_ENTRY

BRANCH_CX_FLAG		equ 01B	; XX_BRANCH_ENTRY.Link.Blink
EhJcxType			equ JCC_ENTRY.Link.Blink	; BRANCH_CX_FLAG

EhKitFlags		equ BLOCK_ENTRY.KitFlags
EhCrossLink		equ JCC_ENTRY.CrossLink

; ��� ��������� ����������� ���������� ���� �� ������. ����� ��������� � LDE �� 
; �����������, � ����������� ��������� ��� ���������. ��� ��������� ������������ 
; ���������(����� �� ��� � ��������� ��������).

JCC_SHORT_OPCODE_BASE	equ 70H
JCC_NEAR_OPCODE_BASE	equ 80H

JCC_O	equ 0	; OF
JCC_NO	equ 1	; !OF
JCC_C	equ 2	; CF
JCC_B	equ 2	; CF
JCC_NAE	equ 2	; CF
JCC_NC	equ 3	; !CF
JCC_NB	equ 3	; !CF
JCC_AE	equ 3	; !CF
JCC_Z	equ 4	; ZF
JCC_E	equ 4	; ZF
JCC_NZ	equ 5	; !ZF
JCC_NE	equ 5	; !ZF
JCC_NA	equ 6	; CF | ZF
JCC_BE	equ 6	; CF | ZF
JCC_A	equ 7	; !CF & !ZF
JCC_NBE	equ 7	; !CF & !ZF
JCC_S	equ 8	; SF
JCC_NS	equ 9	; !SF
JCC_P	equ 0AH	; PF
JCC_PE	equ 0AH	; PF
JCC_NP	equ 0BH	; !PF
JCC_PO	equ 0BH	; !PF
JCC_L	equ 0CH	; SF != OF
JCC_NGE	equ 0CH	; SF != OF
JCC_NL	equ 0DH	; SF = OF
JCC_GE	equ 0DH	; SF = OF
JCC_NG	equ 0EH	; ZF | (SF != OF)
JCC_LE	equ 0EH	; ZF | (SF != OF)
JCC_G	equ 0FH	; !ZF & (SF = OF)
JCC_NLE	equ 0FH	; !ZF & (SF = OF)

; o Jump short: 0x70 + JCC_*
; o Jump near: 0x0F 0x80 + JCC_*

JCC_LOOPNE	equ 0E0H	; Ecx & !ZF
JCC_LOOPE		equ 0E1H	; Ecx & ZF
JCC_LOOP		equ 0E2H	; Ecx
JCC_ECXZ		equ 0E3H	; !Ecx

JCX_OPCODE_BASE	equ 0E0H

JCC_TYPE_MASK		equ 00001111B	; BLOCK_ENTRY.KitFlags
EhJccType			equ BLOCK_ENTRY.KitFlags	; JCC_TYPE_MASK
JCC_X16_MASK		equ 00010000B	; BLOCK_ENTRY.KitFlags, Pfx 0x67

BRANCH_DELTA_SIGN	equ 00100000B	; ���� ��������(0: +, 1: -).

EhBranchOffset		equ EhUserData	; �������� ��������� � ���������� ����.

FLOW_UNLINK_MARK	equ 01000000B	; ���� ������������ ��� �������� ������.
EhFlowMark		equ BLOCK_ENTRY.KitFlags	; FLOW_UNLINK_MARK

CROSS_TYPE_MASK	equ 10000000B	; ���� ����, �� CrossLink �������� ����� ����������.
EhCrossType		equ EhKitFlags

VIRT_IP_MASK		equ 100000000B	; ����������� ����������.
EhVirtFlag		equ EhKitFlags