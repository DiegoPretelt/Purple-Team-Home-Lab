# Root Account Usage

## Summary
Flags any Root user api activity, as root should not be used for managerial or operational duties, this raises a critical level alert of potential exploitation.

## Data Source
- AWS CloudTrail (CloudWatch Logs: /cloudsoc/cloudtrail)

## Detection Logic
**Metric Filter Pattern**
```text
{ $.userIdentity.type = "Root" }
