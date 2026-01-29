# iam-privilege-escalation-attempt

## Summary
This detects any attempts to attach user policy to any user whilst the executing identity does not have the permissions to do so. High likelihood of malicious activity.

## Data Source
- AWS CloudTrail (CloudWatch Logs: /cloudsoc/cloudtrail)

## Detection Logic
**Metric Filter Pattern**
```text
{ ($.eventName = "AttachUserPolicy") && ($.errorCode = "AccessDenied") }
