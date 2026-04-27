## Migrating to esp32-arduino v3.x.x.


## Binary Patching libnet80211.a ##
The function ieee80211_raw_frame_sanity_check returns 0 on success and != 0 on failure. We will force it to always return 0.
1. Locate the signature:

  asm

    riscv32-esp-elf-objdump -d libnet80211.a | grep -A 15 "<ieee80211_raw_frame_sanity_check>:"

    00000000 <ieee80211_raw_frame_sanity_check>:
      0:   7179                    addi    sp,sp,-48
      2:   d606                    sw      ra,44(sp)
      4:   d422                    sw      s0,40(sp)
      6:   d226                    sw      s1,36(sp)
      8:   d04a                    sw      s2,32(sp)
      a:   ce4e                    sw      s3,28(sp)
      c:   cc52                    sw      s4,24(sp)
      e:   ca56                    sw      s5,20(sp)
      10:   c85a                    sw      s6,16(sp)
      12:   e995                    bnez    a1,46 <.L1119>
      14:   000006b7                lui     a3,0x0
      18:   00068693                mv      a3,a3
      1c:   4605                    li      a2,1
      1e:   04000593                li      a1,64
      22:   4505                    li      a0,1

2. Apply the Patch:
Using the provided libnet_patcher.py script, we replace the signature with:

  asm

    0: 4501      li a0, 0
    2: 8082      ret

3. Verify:

  asm

    riscv32-esp-elf-objdump -d libnet80211.a | grep -A 5 "<ieee80211_raw_frame_sanity_check>:"
    00000000 <ieee80211_raw_frame_sanity_check>:
      0:   4501                    li      a0,0
      2:   8082                    ret
      4:   0001                    nop
      6:   0001                    nop
      8:   0001                    nop
      a:   0001                    nop
      c:   0001                    nop
      e:   0001                    nop
      10:   0001                    nop
      12:   0001                    nop
      14:   000006b7                lui     a3,0x0
      18:   00068693                mv      a3,a3
      1c:   4605                    li      a2,1
      1e:   04000593                li      a1,64
      22:   4505                    li      a0,1

Success!


Best wishes,
    Anton
