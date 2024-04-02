# _philosophers
## 프로젝트 개요
> "dining philosopher problem"의 시뮬레이션을 구현.
* philo_basic : 철학자 한 명이 쓰레드라고 보고, 멀티쓰레드 상황에서의 동시성 문제를 해결하기 위해 뮤택스를 사용
* philo_bonus : 철학자 한 명이 프로세스라고 보고, 멀티프로세스 상황에서의 동시성 문제를 해결하기 위해 세마포어를 사용

### Language
* C를 이용해서 작성.
* 다음과 같은 함수만을 이용해서 파일을 작성했습니다.
```{bash}
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
```

## 특징
* 철학자는 한 번에 하나의 활동만 할 수 있습니다.
* 철학자들은 식사하기, 생각하기, 자기 세 가지 활동을 반복합니다.
* 각 철학자는 오른쪽과 왼쪽에 하나씩 포크를 가지고 있습니다.
* 두 개의 포크를 모두 사용해서 식사를 해야 합니다.
* 철학자들이 굶어 죽지 않도록 관리해야 합니다.

## 주요 개념 
* 멀티쓰레드 : [참고링크](https://en.wikipedia.org/wiki/Multithreading_(computer_architecture))
* 멀티프로세스 : [참고링크](https://en.wikipedia.org/wiki/Multiprocessing)
* 동시성 문제 : [참고링크](https://en.wikipedia.org/wiki/Concurrency_(computer_science))
* 뮤택스 & 세마포어 : [참고링크](https://en.wikipedia.org/wiki/Lock_(computer_science)#Mutexes_vs._semaphores)

## 실행 방법
1. 컴파일: Makefile을 사용하여 프로그램을 컴파일.
2. philo_basic : `./philo (철학자 수) (생존 시간) (식사 시간) (자는 시간) (먹는 횟수)`
2. philo_bonus : `./philo_bonus (철학자 수) (생존 시간) (식사 시간) (자는 시간) (먹는 횟수)`

### tips
* `(식사 시간) + (자는 시간)`이 `(생존 시간)`보다 크면 철학자가 죽습니다.
* `(먹는 횟수)`는 옵션입니다.
* philo_basic과 philo_bonus 모두 이와 같은 방법으로 실행합니다.

```{bash}
# 시간 안에 죽는 확인
./philo 4 60 200 200

# 반드시 철학자가 죽는 상황
./philo 1 800 200 200
./philo 5 410 200 200
./philo 4 310 200 100

# 철학자가 무한히 사는 상황
./philo 4 410 200 200
./philo 5 610 200 200
./philo 5 800 200 200

# 철학자가 무한히 사는 상황 (고난이도)
./philo 199 610 200 200 
./philo 200 410 200 200
```

## 구성 파일
### philo_basic
* philo_main.c: 프로그램의 메인 함수가 포함되어 있습니다.
* philo_info.h: 구조체 정의와 헤더 파일들이 포함되어 있습니다.
* philo_input.c: 입력 파라미터 처리 관련 함수가 포함되어 있습니다.
* philo_exe.c: 철학자의 행동을 시뮬레이션하는 주요 함수가 포함되어 있습니다.
* philo_check.c: 철학자의 상태를 체크하는 함수가 포함되어 있습니다.
* util_func.c, util_other.c: 유틸리티 함수가 포함되어 있습니다.

### philo_bonus
* philo_bonus_main.c: 프로그램의 메인 함수를 포함합니다.
* philo_bonus_info.h: 구조체와 세마포어 관련 헤더 파일들을 포함합니다.
* philo_bonus_exe.c, philo_bonus_child.c: 철학자의 행동을 시뮬레이션하는 주요 함수들을 포함합니다.
* philo_bonus_func.c: 도움이 되는 기능들을 포함합니다.
* philo_bonus_util.c, philo_bonus_libft.c: 유틸리티 함수들을 포함합니다.