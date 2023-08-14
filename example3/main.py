from __future__ import annotations
import cv2
from abc import ABC, abstractmethod

class Context:
    _state = None
    handleNumber = None
    img = None
    color = None

    def __init__(self, state: State) -> None:
        self.transition_to(state)

    def transition_to(self, state: State):
        self._state = state
        self._state.context = self

    def handleRequest1(self):
        self._state.handle1()
    
    def handleRequest2(self):
        self._state.handle2()
    
    def update(self):
        self._state.update()

class State(ABC):
    @property
    def context(self) -> Context:
        return self._context
    
    @context.setter
    def context(self, context: Context) -> None:
        self._context = context
    
    @abstractmethod
    def handle1(self) -> None:
        pass
    
    @abstractmethod
    def handle2(self) -> None:
        pass

    @abstractmethod
    def update(self) -> None:
        cv2.putText(self._context.img, f"{self._context.handleNumber}", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, self._context.color, 2)
        cv2.imshow("Img", self._context.img)

class HandleState1(State):
    def handle1(self) -> None:
        print("Handle State 1")

    def handle2(self) -> None:
        print("Transition to Handle State 2")
        self.context.transition_to(HandleState2())

    def update(self) -> None:
        self.context.color = (0, 0, 255)
        self.context.handleNumber = "Handle1"
        return super().update()
    
class HandleState2(State):
    def handle1(self) -> None:
        print("Transition to Handle State 1")
        self.context.transition_to(HandleState1())
    
    def handle2(self) -> None:
        print("Handle State 2")

    def update(self) -> None:
        self.context.color = (255, 0, 0)
        self.context.handleNumber = "Handle2"
        return super().update()

if __name__ == "__main__":
    context = Context(HandleState1())
    context.transition_to(HandleState1())
    while True:
        context.img = cv2.imread("./example3/img/image.png")
        context.update()
        key = cv2.waitKey(1) & 0xFF
        if key == ord("q"):
            break
        elif key == ord("1"):
            context.handleRequest1()
        elif key == ord("2"):
            context.handleRequest2()
    cv2.destroyAllWindows()

    