# M5Stack��MAMORIO��iBeacon�ʐM���L���v�`�����\������
M5Stack���g���āA���ӂɗ���Ă���MAMORIO��iBeacon packet���L���v�`�����A�V���A���^�[�~�i���ɕ\�����Ă����B

MAMORIO�Ƃ́A�s�̂�BLE�����h�~�^�O�ł���B
����J�o���ȂǂɎ��t���A�莝���̃X�}�z�ƘA�g���ĖY���̂�h���ړI�Ŏg�p����B

<img src="mamorio.jpg" alt="mamorio.jpg" title="�T���v��">


�\������V���A���^�[�~�i���̃{�[���[�g��115200bps�B

<img src="teraterm.jpg" alt="�V���A���^�[�~�i���\����" title="�T���v��">

PC�̃V���A���^�[�~�i���ɁAM5Stack��TypeC USB�P�[�u����ڑ��B
TypeC USB�R�l�N�^��ESP32��UART0�ɂȂ����Ă���B


## �v���O�����̎d�l

### Setup()�֐�
ESP32��UART0�̃{�[���[�g��115200bps�ɐݒ�B
M5Stack��LCD��ʔw�i��Navy�F�ɂ��A����������"START"�ƕ\������B
�i���������̉�ʐݒ�́A����loop()�֐��ɂ�肷���ɏ㏑�������̂ŁA���ۂ͌����Ȃ��B�j

### loop()�֐�
Setup�֐��ɂ�鏈�����I������炱����̊֐������s�����B
1) M5Stack��LCD��ʔw�i�����F�ɂ��A����������"Scan MAMORIO start!"�ƕ\������B
2) BLE����������B
3) BLE�ł�Advertizing packet�̃X�L�������J�n����B
�@�X�L�����́AscanTime�@�Œ�`���ꂽ���ԕ��A�p������B
4) scanTime�@�Œ�`���ꂽ���Ԃ��o�߂�����A�X�L�������I������B

### BLEAdvertisedDeviceCallbacks()�֐�
Advertizing packet�����o���ꂽ��Ă΂��֐��B
���̒��ŁAiBeacon�̏ꍇ�AMAMORIO�����ǂ������`�F�b�N���V���A���^�[�~�i���ɕ\�����Ă���B

