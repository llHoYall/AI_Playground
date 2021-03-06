# Neuron

생물의 신경 세포는 다른 여러 신경 세포로부터 신호를 받아 세포 안에서 처리를 시행한 다음, 출력 신호를 다른 신경 세포로 보낸다.

인공 신경은 이 움직임을 단순화하여 수학적으로 흉내 낸 계산 소자이다.

## 신경망의 학습 과정

1. 모든 가중치와 문턱값을 초기화한다.
2. 다음을 적당한 횟수 반복한다.
	1. 학습 data 집합에서 하나의 학습 예를 골라 신경망에 넣어 출력을 계산한다.
	2. 교사 data와 신경망의 출력을 비교하여 오차가 적어지도록 가중치와 문턱값을 조절한다.

## 하나의 인공 신경에서 입력 신호에 대한 출력값 계산 과정

1. 가중치와 문턱값 초기화한다.
2. 입력 data를 읽는다.
3. 다음을 모든 입력 data에 대해 계산한다.
	1. 입력값과 이에 다한 다중치를 곱하여 모두 더한다.
	2. 문턱값을 뺀다.
	3. 전달 함수를 이용하여 출력값을 계산한다.
