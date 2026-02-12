"""
Character statistics system.
"""

from dataclasses import dataclass
from typing import Optional


@dataclass
class Stats:
    """Character base statistics (force, dexterity, intelligence)."""
    strength: int = 100
    intelligence: int = 100
    wisdom: int = 0
    dexterity: int = 100
    constitution: int = 0
    charisma: int = 0

    def modify(self, stat_name: str, amount: int):
        """Modify a stat by amount."""
        if hasattr(self, stat_name):
            current = getattr(self, stat_name)
            setattr(self, stat_name, max(0, current + amount))


@dataclass
class StatusEffects:
    """Active status effects on character."""
    is_paralyzed: bool = False
    is_blind: bool = False
    is_confused: bool = False
    is_poisoned: bool = False
    is_hallucinating: bool = False
    is_hasted: bool = False
    is_slowed: bool = False
    is_stunned: bool = False
    is_teleporting: bool = False
    has_detect: bool = False
    has_light: bool = False
    is_invulnerable: bool = False

    # Timers (turns remaining)
    paralyze_timer: int = 0
    blind_timer: int = 0
    confusion_timer: int = 0
    poison_timer: int = 0
    hallucination_timer: int = 0
    haste_timer: int = 0
    slow_timer: int = 0
    stun_timer: int = 0
    detect_timer: int = 0
    light_timer: int = 0
    invulnerable_timer: int = 0

    def update(self):
        """Update timers and effects each turn."""
        # Decrement timers
        if self.paralyze_timer > 0:
            self.paralyze_timer -= 1
            if self.paralyze_timer == 0:
                self.is_paralyzed = False

        if self.blind_timer > 0:
            self.blind_timer -= 1
            if self.blind_timer == 0:
                self.is_blind = False

        if self.confusion_timer > 0:
            self.confusion_timer -= 1
            if self.confusion_timer == 0:
                self.is_confused = False

        if self.poison_timer > 0:
            self.poison_timer -= 1
            if self.poison_timer == 0:
                self.is_poisoned = False

        if self.hallucination_timer > 0:
            self.hallucination_timer -= 1
            if self.hallucination_timer == 0:
                self.is_hallucinating = False

        if self.haste_timer > 0:
            self.haste_timer -= 1
            if self.haste_timer == 0:
                self.is_hasted = False

        if self.slow_timer > 0:
            self.slow_timer -= 1
            if self.slow_timer == 0:
                self.is_slowed = False

        if self.stun_timer > 0:
            self.stun_timer -= 1
            if self.stun_timer == 0:
                self.is_stunned = False

        if self.detect_timer > 0:
            self.detect_timer -= 1
            if self.detect_timer == 0:
                self.has_detect = False

        if self.light_timer > 0:
            self.light_timer -= 1
            if self.light_timer == 0:
                self.has_light = False

        if self.invulnerable_timer > 0:
            self.invulnerable_timer -= 1
            if self.invulnerable_timer == 0:
                self.is_invulnerable = False

    def apply_paralysis(self, duration: int):
        """Apply paralysis effect."""
        self.is_paralyzed = True
        self.paralyze_timer = max(self.paralyze_timer, duration)

    def apply_blindness(self, duration: int):
        """Apply blindness effect."""
        self.is_blind = True
        self.blind_timer = max(self.blind_timer, duration)

    def apply_confusion(self, duration: int):
        """Apply confusion effect."""
        self.is_confused = True
        self.confusion_timer = max(self.confusion_timer, duration)

    def apply_poison(self, duration: int):
        """Apply poison effect."""
        self.is_poisoned = True
        self.poison_timer = max(self.poison_timer, duration)

    def apply_hallucination(self, duration: int):
        """Apply hallucination effect."""
        self.is_hallucinating = True
        self.hallucination_timer = max(self.hallucination_timer, duration)

    def apply_haste(self, duration: int):
        """Apply haste effect."""
        self.is_hasted = True
        self.haste_timer = max(self.haste_timer, duration)

    def apply_detect(self, duration: int):
        """Apply detection effect."""
        self.has_detect = True
        self.detect_timer = max(self.detect_timer, duration)

    def can_act(self) -> bool:
        """Check if character can take actions."""
        return not self.is_paralyzed
